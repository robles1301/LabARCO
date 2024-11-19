#Task 1

## Questions

1. Before starting any analysis on the code, it is interesting to know the characteristics of the architecture on which you are running the program, so answer the following questions:

    * Indicate your processor model, architecture, and how many cores and processing threads you have.
    * How many threads can be executed per core?
    
- processor model: 11th Gen Intel(R) Core(TM) i5-11400H @ 2.70GHz
- architecture: x86_64
- number of cores: 6
- number of threads: 12
- number of threads per core: 2

2. Perform a complete analysis from the CPU/Roofline view. From the "Survey & Roofline" tab, analyze the Top Down result.
	*Which function of our business logic consumes the most time?
    
 - the function to run detection (void runDetector)
 
 	*Which stages are the most costly?
 
 -inside rundetecion function we find three stage. Main stage(LBL_FAD_Stage3_4) 4,2 sec, read_Integer_Matrix 2,73 sec in Main_Detector_HW.cpp, disc write (write_txt_file) 0,75 sec
  
	*Which operations (we understand operations as the functions defined in LBL_FAD_Transform_Operations.h/.cpp) are the most complex and require the most time?
	
- subtractingInformation 2,1secin LBL_FAD_Stage3_4, projectingImg 1.53 sec, brightnessAD 0,29 sec and duplicateAndCentralizeImg 0,28 sec

Perform a complete analysis and show a screenshot of the roofline graph.

	*What are the three most complex loops? Why are they limited? How would you improve them?
	
subtractingInformation line 269 in LBL_FAD_Transform_Operations.cpp, vectorization
 projectingImg line 247 in LBL_FAD_Transform_Operations.cpp, calculation restructuring
 write_txt_file line 67 in Main_Detector_HW.cpp, memory write and dump to disc
 
 
 3. Perform a "refinement" analysis by adding the Memory Access Patterns step and select the two loops that consume the most time performing internal calculations.
 	
 	*Indicate which two loops they are.
 	
 	* What types of memory access are being performed? Which ones exist?

 
- Loop Analysis in subtractingInformation
Memory Access Type: Scalar read and write and multiples array access-

 
- Loop Analysis in projectingIMG
Memory Access Type: Mainly read.



 
 
   
