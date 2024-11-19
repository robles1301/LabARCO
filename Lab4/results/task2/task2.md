1. Review the code and answer the following questions:

* Which loops have been annotated?

loop in subtractingInformation (line 269)
loop in projectingImg (line 247)
loop in write_txt_file (line 67)

These are the loops that consume significant computational resources and are candidates for optimization through parallelization.

* What structure does an annotation follow? Into what parts is it decomposed?

three parts: marking parallel regions (ANNOTATE_SITE_BEGIN and ANNOTATE_SITE_END), marking tasks within the site (ANNOTATE_ITERATION_TASK or ANNOTATE_TASK_BEGIN/ANNOTATE_TASK_END) and finally attributes but it is optional

* Annotations are like pseudocode of how we would parallelize with OpenMP. What does each part of the annotation correspond to in OpenMP?

ANNOTATE_SITE_BEGIN/END -> #pragma omp parallel

ANNOTATE_ITERATION_TASK -> #pragma omp for

ANNOTATE_TASK_BEGIN/END -> #pragma omp task

2. Once the "Suitability" analysis is executed, go to the Suitability Report tab and answer the following questions:

* What do each of the columns in the top table mean?
Columns in the Top Table
Site Gain:
The potential performance improvement if this site is parallelized.

Impact to Program Gain:
The contribution of this site to the overall program's speedup if parallelized.

Source Location:
Location in files.

Time:
Total time of execution (Total serial time and total parallel time).

* What is the difference between Impact to Program Gain and "Site Gain"?

in site gain, the local speedup for that specific site if parallelized while impact to program gain is the overall effect on the entire program, considering this site's runtime relative to the total runtime.

* Which loops would you parallelize? With which loop would you achieve the highest performance?

The loop in subtractingInformation has the needed of highest Performance due to its long duration and high number of iterations.

Rest of loops to Parallelize:
loop in subtractingInformation
loop in projectingImg

* How do duration and number of iterations affect the expected performance? Use screenshots to support the analysis.

Duration:
Longer duration loops benefit more from parallelization because the workload can be distributed also threading overhead become less significant.

Number of Iterations:
Higher number of iterations indicates a large workload to distribute, which generally improves scalability.

* What does the number of iterations in each "site" correspond to in the code? What is its function within the algorithm?

The number of iterations corresponds to the loop count for that specific code region. 
For example, the iteration in the loop from subtractingInformation represent the number of elements being processed.

