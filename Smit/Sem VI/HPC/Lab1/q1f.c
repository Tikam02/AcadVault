    
#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#define LL long long

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


int main(void) 
{
    LL int min_size = pow(2,3);
    LL int max_size = pow(2,10);
    LL int total = max_size;
    LL int i,j,k,l,kk,jj,size,cache_size,runs;
    LL int RUNS = 5;
    double start_time_c, end_time_c, start_time, end_time, d;

    for(size = min_size; size <= max_size; size *= 2) {
        double** A = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            A[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                A[i][j] = 2.5 + i%(j+1);
            }
        }   

        double** B = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            B[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                B[i][j] = 3.75 + j%(i+1);
            }
        }

        double** C = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            C[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                C[i][j] = 0;
            }
        }
        LL int MATRIX_SIZE = size;
//i j k
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf ", end_time);
//i k j
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf ", end_time);
//j i k
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf ", end_time);
//j k i
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf ", end_time);
//k i j
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf ", end_time);
//k j i
        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for (k = 0; k < MATRIX_SIZE; k += 1)
                for (j = 0; j < MATRIX_SIZE; j += 1)
                    for (i = 0; i < MATRIX_SIZE; ++i)
                                C[i][j] += A[i][k] * B[k][j];
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        printf("%lf\n", end_time);
    }
}