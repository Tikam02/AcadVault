/*#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

long minSize,maxSize,total,size,i,j,k,bi,bj,bk,temp,blockSize,sum;
double throughput,runs,**a,**b,**c;

int main(){
    minSize = pow(2,4);
    maxSize = pow(2,10);
    total = maxSize;
    for(size=minSize;size<maxSize;size*=2){
        runs = (double)total/size;
       
        a=(double**)calloc(size,sizeof(double*));
        b=(double**)calloc(size,sizeof(double*));
        c=(double**)calloc(size,sizeof(double*));
       
        for(i=0;i<size;i++){
            a[i]=(double*)calloc(size,sizeof(double));
            b[i]=(double*)calloc(size,sizeof(double));
            c[i]=(double*)calloc(size,sizeof(double));
        }

        double start_time = omp_get_wtime();
        for(temp=0;temp<(long)runs;temp++){
            for(i=0;i<size;i++)
               for(j=0;j<size;j++){
                sum=0;
                for(k=0;k<size;k++) sum+=a[i][k]*b[k][j];
                c[i][j]=temp;
                }
            if(temp==maxSize) temp++;
        }

        double end_time = omp_get_wtime() - start_time;
        throughput = (sizeof(double)*2*total)/(double)end_time;

        printf("%lf,",throughput);
        free(a);free(b);free(c);   

        
        
        a=(double**)calloc(size,sizeof(double*));
        b=(double**)calloc(size,sizeof(double*));
        c=(double**)calloc(size,sizeof(double*));
       
        for(i=0;i<size;i++){
            a[i]=(double*)calloc(size,sizeof(double));
            b[i]=(double*)calloc(size,sizeof(double));
            c[i]=(double*)calloc(size,sizeof(double));
        }

        if(size<100) blockSize = size;
        else blockSize = 128;

        start_time = omp_get_wtime();
        for(temp=0;temp<(long)runs;temp++){
            for(bi=0;bi<size;bi+=blockSize)
             for(bj=0;bj<size;bj+=blockSize)
              for(bk=0;bk<size;bk+=blockSize)
               for(i=0;i<blockSize;i++)
                for(j=0;j<blockSize;j++){
                sum=0;
                for(k=0;k<blockSize;k++) sum+=a[bi+i][bk+k]*b[bk+k][bj+j];
                c[bi+i][bj+j]=temp;
                }
            if(temp==maxSize) temp++;
        }

        end_time = omp_get_wtime() - start_time;
        throughput = (sizeof(double)*2*total)/(double)end_time;

        printf("%lf,",throughput);
        free(a);free(b);free(c);    
    }
}*/

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

int main(void) {
    LL int min_size = pow(2,3);
    LL int max_size = pow(2,10);
    LL int total = max_size;
    LL int i,j,k,l,kk,jj,size,cache_size,runs;
    LL int RUNS = 5;
    double start_time_c, end_time_c, start_time, end_time, d;

    printf("Problem Size\tCompute Time\t\tCMA\n");

    int size_array[8];
    float compute_time_array[8], CMA_array[8];

    // Standard Algorithm
    for(size = min_size; size <= max_size; size *= 2) {
       
        double** A = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            A[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                A[i][j] = 2.5;
            }
        }   

        double** B = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            B[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                B[i][j] = 3.75;
            }
        }

        double** C = (double**) malloc(size * sizeof(double*));
        for(i = 0; i < size; i++) {
            C[i] = (double*)malloc(size * sizeof(double));   
            for(j = 0; j < size; j++) {
                C[i][j] = 0;
            }
        }

        // Calculate Compute Time
        start_time_c = omp_get_wtime();
        for(i = 0; i < size; i++) {
            for(j = 0; j < size; j++) {
                for(k = 0; k < size; k++) {
                    d = 1 + 2 * 3;
                }
            }
        }
        end_time_c = omp_get_wtime() - start_time_c;
       

        start_time = omp_get_wtime();
        for(runs = 0; runs < RUNS; runs++) {
            for(i = 0; i < size; i++) {
                for(j = 0; j < size; j++) {
                    for(k = 0; k < size; k++) {
                        C[i][j] = C[i][j] + A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime() - start_time;
        end_time /= RUNS;

        size_array[size/min_size -1] = size;
        compute_time_array[size/min_size -1] = end_time;
        CMA_array[size/min_size -1] = (end_time_c)/(end_time - end_time_c);
        // printf("%lld\t\t%f\t\t%f\n", size, end_time, (end_time_c)/(end_time - end_time_c));
    }   
    int kg=0;
    for(kg=0; kg<8; kg++) {
        printf("%d ", size_array[i]);
    }
    printf("\n");
    for(kg=0; kg<8; kg++) {
        printf("%f ", compute_time_array[i]);
    }
    printf("\n");
    for(kg=0; kg<8; kg++) {
        printf("%f ", CMA_array[i]);
    }
    printf("\n");

    printf("================================================================");

    printf("\n");
/*
    // 2D Blocled MM
    LL int min_cache_line = pow(2,2);
    LL int max_cache_line = pow(2,7);

    for(cache_size = min_cache_line; cache_size <= max_cache_line; cache_size *= 2) {
        printf("\n\n\nCache Size: %lld", cache_size);
        // printf("\n\nProblem Size\tCompute Time\t\tCMA\n");

        for(size = min_size; size <= max_size; size *= 2) {
            double** A = (double**) malloc(size * sizeof(double*));
            for(i = 0; i < size; i++) {
                A[i] = (double*)malloc(size * sizeof(double));   
                for(j = 0; j < size; j++) {
                    A[i][j] = 2.5;
                }
            }   

            double** B = (double**) malloc(size * sizeof(double*));
            for(i = 0; i < size; i++) {
                B[i] = (double*)malloc(size * sizeof(double));   
                for(j = 0; j < size; j++) {
                    B[i][j] = 3.75;
                }
            }

            double** C = (double**) malloc(size * sizeof(double*));
            for(i = 0; i < size; i++) {
                C[i] = (double*)malloc(size * sizeof(double));   
                for(j = 0; j < size; j++) {
                    C[i][j] = 0;
                }
            }

            // Calculate Compute Time
            start_time_c = omp_get_wtime();
            for(i = 0; i < size; i++) {
                for(j = 0; j < size; j++) {
                    for(k = 0; k < size; k++) {
                        d = 1 + 2 * 3;
                    }
                }
            }
            end_time_c = omp_get_wtime() - start_time_c;

            LL int MATRIX_SIZE = size;
            LL int block_size = cache_size;

            start_time = omp_get_wtime();
            for(runs = 0; runs < RUNS; runs++) {
                for (k = 0; k < MATRIX_SIZE; k += block_size)
                    for (j = 0; j < MATRIX_SIZE; j += block_size)
                        for (i = 0; i < MATRIX_SIZE; ++i)
                            for (jj = j; jj < min(j + block_size, MATRIX_SIZE); ++jj)
                                for (kk = k; kk < min(k + block_size, MATRIX_SIZE); ++kk)
                                    C[i][jj] += A[i][kk] * B[kk][jj];
            }
            end_time = omp_get_wtime() - start_time;
            end_time /= RUNS;

            // printf("%lld\t\t%f\t\t%f\n", size, end_time, (end_time_c)/(end_time - end_time_c));
            
            size_array[size/min_cache_line -1] = size;
            compute_time_array[size/min_cache_line -1] = end_time;
            CMA_array[size/min_cache_line -1] = (end_time_c)/(end_time - end_time_c);

            int i=0;
            for(i=0; i<8; i++) {
                printf("%lld ", size_array[i]);
            }
            printf("\n");
            for(i=0; i<8; i++) {
                printf("%f ", compute_time_array[i]);
            }
            printf("\n");
            for(i=0; i<8; i++) {
                printf("%f ", CMA_array[i]);
            }
            printf("\n");

            printf("================================================================");

            printf("\n");
        }
    }
*/
   
}

