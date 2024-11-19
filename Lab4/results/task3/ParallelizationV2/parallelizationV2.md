
## Parallelization v2

### Preliminary Analysis
Indicate what you based your decision on to parallelize this region of code, support your argument with screenshots from Intel Advisor.

These regions exhibited a high percentage of accumulated execution time and an absence of data dependencies between iterations, making them suitable for parallelization



### Parallelization 
Explain the modifications made to the original code.

void averagePixel(unsigned short *ImgRef, int *centroid, int blockSize) {
  #pragma omp parallel for
  for (int band = 0; band < BANDS; band++)
  
void duplicateAndCentralizeImg(unsigned short *ImgRef, short *Img, int *centroid, int blockSize) {
  #pragma omp parallel for collapse(2)
  for (int pixel = 0; pixel < blockSize; pixel++)
  for (int band = 0; band < BANDS; band++)
  
void brightness(short *Img, int &maxIndex, long long &maxBrightness, unsigned char iter, long long *brightness_iter1, int blockSize)

#pragma omp parallel
  {
    long long localMaxBrightness = 0;
    int localMaxIndex = 0;

    #pragma omp for
    for (int pixel = 0; pixel < blockSize; pixel++)
    
#pragma omp critical
{
 if (localMaxBrightness > maxBrightness)
 

-We use parallel for, for dividing the loops into differents threads with the aim of taking benefit from every CPU core.  

-We use parallel critical only one threads to avoid the race conditon

-We usea parallel for collapse to combine to iteration in only one thread

Did you have to modify how any variable is calculated to avoid inter-loop dependencies?

No, because if we modifed the code give us segmantation fault, and we can't analyse the code.

### Post Analysis
Compare the original code with the improved one and create comparison tables by increasing the number of threads.

* Do the results match the value predicted by the tool?
yes, it was pretty close

* How did you compare the results to verify the correctness of the parallel program?
with intel advisor we show that in the parallel program the times were lower than the original one.
As we can see in the white table (the black table is the original program)


| Number of threads | `subtractingInformation` | `projectingImg` | `LBL_FAD_Stage3_4` | `duplicateAndCentralizeImg` | `runDetector (LBL_FAD_Stage3_4 loop)` |
|-----------------|--------------------------|-----------------|--------------------|-----------------------------|---------------------------------------|
| 2               | 0.847 s                  | 0.743 s         | 1.395 s            | 0.153 s                     | 1.868 s                               |
| 4               | 0.473 s                  | 0.415 s         | 0.779 s            | 0.085 s                     | 1.044 s                               |
| 6               | 0.358 s                  | 0.314 s         | 0.589 s            | 0.064 s                     | 0.789 s                               |





