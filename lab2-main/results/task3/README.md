| Number of threads | Execution time (s) | Directive           | Pi results   |
|-----------------|-------------------------|---------------------|-------------------|
| -             | 0.000001                    | no Directive |      3.1449258640033282       |
| 1               | 0.005017                     | #pragma omp parallel| 3.1449258640033282         |
| 2               | 0.004972                     | #pragma omp parallel| 3.1449258640033277          |
| 4               | 0.003833                     | #pragma omp parallel| 3.1449258640033265           |


| Number of threads | Execution time (s) | Directive           | Pi results   |
|-----------------|-------------------------|---------------------|-------------------|
| 1               | 0.005956                     | #pragma omp critical| 3.1449258640033278         |
| 2               | 0.004673                     | #pragma omp critical| 3.1449258640033298          |
| 4               | 0.003126                     | #pragma omp critical| 3.1449258640033223           |