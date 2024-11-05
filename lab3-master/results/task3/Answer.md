# Task 3: Ansewers
## Questions

1. Before starting the vectorization process, it is crucial to understand the specifics of your machine. What are the SIMD multimedia extensions available on your architecture?

- My SIMD multimedia availeable: AVX2, AVX, SSE2, SSE

2. Review the analysis you've conducted on the complexmul.cpp program. Intel Advisor should have identified an underutilization of instructions, directly related to vectorization, as it indicates that you have available SIMD extensions that are not being leveraged. To vectorize the algorithm, Intel Advisor itself provides guidance on how to proceed. What steps have you taken to vectorize the loop? Keep in mind that you should pursue maximum vectorization that your architecture permits.

- #pragma omp parallel for

        for(int i = 0; i < SIZE; i++) {
        
        a[i][REAL] = sin((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        a[i][IMAG] = cos((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        b[i][REAL] = sin((6*seed*i * ( seed*i - 1) + 1));
        b[i][IMAG] = cos((6*seed*i * ( seed*i - 1) + 1));
        }

- #pragma omp parallel for

        for(int i = 0; i < SIZE; i++) {
        #pragma omp simd
        for(int j = 0; j < SIZE; j++) {
            c[i][REAL] += (a[i][REAL] * b[j][REAL]) - (a[i][IMAG] * b[j][IMAG]);
            c[i][IMAG] += (a[i][IMAG] * b[j][REAL]) + (a[i][REAL] * b[j][IMAG]);
        }
        }

3. After vectorizing the program, conduct an analysis and save it under the name "task3":
   * What is the value indicated in the 'Vector Length' field? Considering the extensions you're utilizing and the program's use of 32-bit floats, is this the expected value? Justify the anticipated value, whether the actual value aligns with your expectations or not.
   - The value of vector length is 2, we do not expected that number

   * What was the extent of the improvement? Discuss whether this is the outcome you predicted; if not, explain what you believe might be the reason (Hint: Intel Advisor can offer insights into what the issue might be).
    - The column gains is empty, so we suppose there is not improvement.




