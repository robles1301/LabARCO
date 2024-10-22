#include <stdio.h>
#include <omp.h>  

int main() {
    int arr[] = {12, 3, 45, 2, 8, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0], min = arr[0];
    double start, end;

   
    start = omp_get_wtime();
    
    #pragma omp parallel for shared(max, min)
    for(int i = 1; i < n; i++) {
        #pragma omp critical
        {
            if(arr[i] > max) max = arr[i];
            if(arr[i] < min) min = arr[i];
        }
    }

    
    end = omp_get_wtime();

 
    double execution_time = end - start;

    printf("Max: %d, Min: %d\n", max, min);
    printf("Tiempo de ejecución: %f segundos\n", execution_time);
    return 0;
}
