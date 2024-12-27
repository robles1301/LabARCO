#include <CL/sycl.hpp>
using namespace cl::sycl;
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

#include "LBL_FAD_Transform_Operations.h"
#include "Utils.h"
#include "advisor-annotate.h"
#include "Configurations.h"

// --- Function Signatures
void read_Integer_Matrix(char* inputFileName, unsigned short *input_img);
void write_txt_file(const char* OutputFileName, bool *data, unsigned int size);  
void runDetector(unsigned short *input_img, const char* OutputFileName, sycl::queue &q);  

// --- Main
int main(int argc, char* argv[])
{
    auto selector = sycl::default_selector_v; 
    sycl::queue q(selector);

    if (q.get_device().is_cpu()) {
        std::cout << "El dispositivo seleccionado es una CPU." << std::endl;
    } else if (q.get_device().is_gpu()) {
        std::cout << "El dispositivo seleccionado es una GPU." << std::endl;
    } else {
        std::cout << "El dispositivo seleccionado no es ni CPU ni GPU." << std::endl;
    }
    
    mkdir(OUTPUT_DIR, 0777);

    // Input Img
    unsigned short *input_img;
    input_img = (unsigned short *)malloc(sizeof(unsigned short) * IMAGE_SIZE);
    if (input_img == NULL) {
        std::cerr << "Error al asignar memoria para input_img" << std::endl;
        exit(1);
    }

    // Read the Img
    read_Integer_Matrix((char*)INPUT_FILE_NAME, input_img);

    // Run the detector
    runDetector(input_img, (const char*)OUTPUT_FILE_NAME, q);  

    cout << "--- Finished OK ---" << std::endl;  

    free(input_img);

    return 0;
}

void read_Integer_Matrix(char* inputFileName, unsigned short *input_img)
{
    std::cout << "Intentando abrir el archivo: " << inputFileName << std::endl;
    FILE *inputFile = fopen(inputFileName, "r+b");
    if (inputFile == NULL) {
        std::cerr << "Error al abrir el archivo: " << inputFileName << std::endl;
        exit(1); 
    }

    int numberOfReadElement = 0;
    int bytesPerElement = 2;

    unsigned short readElement;

    while (numberOfReadElement < IMAGE_SIZE) {
        fread(&readElement, bytesPerElement, 1, inputFile);
        input_img[numberOfReadElement] = (unsigned short)readElement;
        numberOfReadElement++;
    }
    fclose(inputFile);
}

void write_txt_file(const char* OutputFileName, bool *data, unsigned int size) 
{
    stringstream outputFilename;
    outputFilename << OUTPUT_DIR << "/" << OUTPUT_FILE_NAME;
    ofstream outputFile;
    outputFile.open(outputFilename.str(), std::ios::app);
    for(unsigned int _it = 0; _it != size; _it++)
        outputFile << data[_it] << std::endl; 
    outputFile.close();
}

// Function for executing the process
void runDetector(unsigned short *input_img, const char* OutputFileName, sycl::queue &q) 
{
    // Initialize and declare the variables
    unsigned int nBlocks = (COLUMNS * LINES) / BLOCK_SIZE;
    unsigned int nInputElementsPerBlock = BLOCK_SIZE * BANDS;

    unsigned short input_block[BLOCK_SIZE * BANDS];
    unsigned short bg_indexes[BLOCK_SIZE * BANDS];
    unsigned short bg_block[BLOCKS_BACKGROUND * MAX_ENDMEMBERS_PER_BLOCK];
    unsigned int n_indexes = 0;

    unsigned int inputIndex = 0;
    unsigned int blockIndex = 0;

    //-----------
    // Stage 1: Background
    //-----------
#ifdef VERBOSE
    cout << ":: Stage 1: Background :: " << std::endl;  
#endif
    ANNOTATE_SITE_BEGIN("First stage block for");
    for (; blockIndex < BLOCKS_BACKGROUND; blockIndex++) {
        ANNOTATE_ITERATION_TASK("for body");
        for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
            input_block[elementIndex] = input_img[inputIndex + elementIndex];
        }
        inputIndex += nInputElementsPerBlock;

        LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block, q);
    }
    ANNOTATE_SITE_END();
    //-------------------

    //-----------
    // Stage 2: Background estimation
    //-----------
#ifdef VERBOSE
    cout << ":: Stage 2: Background estimation :: " << std::endl;  
#endif

    long long tau = 0;
    unsigned char numQU = 0;
    int qMatrix[MAX_NUMQU][BANDS];
    int uMatrix[MAX_NUMQU][BANDS];
    int centroid[BANDS];

    for (unsigned int itIndex = 0; itIndex < n_indexes; itIndex++) {
        for (unsigned int itBands = 0; itBands < BANDS; itBands++) {
            input_block[itIndex * BANDS + itBands] = input_img[bg_block[itIndex] * nInputElementsPerBlock + bg_indexes[itIndex] * BANDS + itBands];
        }
    }

    ANNOTATE_SITE_BEGIN("LBL_FAD_Stage2");
    ANNOTATE_TASK_BEGIN("LBL_FAD_Stage2");
    LBL_FAD_Stage2(input_block, centroid, qMatrix, uMatrix, numQU, tau, n_indexes, q);
    ANNOTATE_TASK_END();
    ANNOTATE_SITE_END();

#ifdef VERBOSE
    cout << ":: TAU :: " << tau << std::endl;  
    cout << ":: numQU :: " << (short)numQU << std::endl;  
#endif
    //-------------------

    //-----------
    // Stage 3: Computation of the orthogonal substage and anomalous targets
    //-----------
#ifdef VERBOSE
    cout << ":: Stage 3: AD Map :: " << std::endl;  
#endif

    bool block_ad_map[BLOCK_SIZE];
    ANNOTATE_SITE_BEGIN("Third stage block for");
    for (; blockIndex < nBlocks; blockIndex++) {
        ANNOTATE_ITERATION_TASK("for body of third stage");
        // Creating the block vector
        for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
            input_block[elementIndex] = input_img[inputIndex + elementIndex];
        }
        inputIndex += nInputElementsPerBlock;

        LBL_FAD_Stage3_4(blockIndex, input_block, numQU, tau, centroid, qMatrix, uMatrix, block_ad_map);

#ifdef VERBOSE_DBG
        if (blockIndex == BLOCK_DBG || BLOCK_DBG == -1) {
            stringstream outputFilename;
            outputFilename << OUTPUT_DIR << "/ad_map_b" << blockIndex << ".txt";
            ofstream outputFile;
            outputFile.open(outputFilename.str());
            for (int it = 0; it != BLOCK_SIZE; it++)
                outputFile << block_ad_map[it] << std::endl;  
            outputFile.close();
        }
#endif

        write_txt_file(OUTPUT_FILE_NAME, block_ad_map, BLOCK_SIZE);  
    }
    ANNOTATE_SITE_END();
    //-------------------
}

