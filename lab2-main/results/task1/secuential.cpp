#include <stdio.h>
#include <time.h>  

int main() {
    int arr[] = {12, 3, 45, 2, 8, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = arr[0], min = arr[0];
    clock_t start, end;
    double cpu_time_used;

  
    start = clock();
    
    for(int i = 1; i < n; i++) {
        if(arr[i] > max) max = arr[i];
        if(arr[i] < min) min = arr[i];
    }

    
    end = clock();

   
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Max: %d, Min: %d\n", max, min);
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);
    return 0;
}
