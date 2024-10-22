| Number of threads | Execution time (s)| Directive           |
|-----------------|-------------------------|---------------------|
| -               | 0.000001                          | without directive   |
| 1               | 0.005471                     | #pragma omp parallel|
| 2               | 0.003646                     | #pragma omp parallel|
| 4               | 0.003869                     | #pragma omp parallel|

| Number of threads | Execution time (s)| Directive           |
|-----------------|-------------------------|---------------------|
| 1               | 0.005673                     | #pragma omp critical|
| 2               | 0.003745                     | #pragma omp critical|
| 4               | 0.003178                     | #pragma omp critical|



