#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <omp.h>  
#define N 50  

int main() {
    int i, sum = 0;
    int v[N];
    double start, end;  

    srand(time(NULL));  
    for (i = 0; i < N; i++) v[i] = rand() % 100;

    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        #pragma omp critical
        sum += v[i];
    }

    end = omp_get_wtime();

    printf("\nVector de números: \n");
    for (i = 0; i < N; i++) printf("%d \t", v[i]);

    printf("\nLa suma es: %d \n", sum);

    printf("Tiempo de ejecución: %f segundos\n", end - start);
    
    return 0;
}
