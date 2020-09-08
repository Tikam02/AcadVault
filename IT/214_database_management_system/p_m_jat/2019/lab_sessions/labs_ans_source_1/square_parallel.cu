#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
 
// CUDA kernel. Each thread takes care of one element of c
__global__ void vecAdd(double *a, double *c, long long n)
{
	// Get our global thread ID
    	int id = blockIdx.x*blockDim.x+threadIdx.x;
 
    	// Make sure we do not go out of bounds
    	if (id < n)
        	c[id] = a[id]*a[id];
}
 
int main( int argc, char* argv[] )
{
    	FILE *fptr = fopen("parallel_square.txt", "w");
	
	long long minsize = pow(2,8);
	long long maxsize = pow(2,28);
	//int cnt = 0;
	//int  n = 20;
	
	long long n;
	
	for(n = minsize; n<maxsize; n*=2)
	{

	// Size of vectors
    	//int n = 1000000;
 
    	// Host input vectors
    	double *h_a;
    	//double *h_b;
    	//Host output vector
    	double *h_c;
 
    	// Device input vectors
    	double *d_a;
    	//double *d_b;
    	//Device output vector
    	double *d_c;
 
    	// Size, in bytes, of each vector
    	size_t bytes = n*sizeof(double);
 
    	// Allocate memory for each vector on host
    	h_a = (double*)malloc(bytes);
    	//h_b = (double*)malloc(bytes);
    	h_c = (double*)malloc(bytes);
 
    	// Allocate memory for each vector on GPU
    	cudaMalloc(&d_a, bytes);
    	//cudaMalloc(&d_b, bytes);
    	cudaMalloc(&d_c, bytes);
 
    	long long i;
    	// Initialize vectors on host
    	for( i = 0; i < n; i++ ) {
        	h_a[i] = sin(i);
        	//h_b[i] = cos(i);
    	}
 
    	cudaEvent_t start, stop;
    	cudaEventCreate(&start);
    	cudaEventCreate(&stop);		

    	// Copy host vectors to device
    	cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    	//cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);
 
    	int blockSize, gridSize;
 
    	// Number of threads in each thread block
    	blockSize = 1024;
 
    	// Number of thread blocks in grid
    	gridSize = (int)ceil((float)n/blockSize);
 
    	cudaEventRecord(start);		
    	// Execute the kernel
    	vecAdd<<<gridSize, blockSize>>>(d_a, d_c, n);
 	cudaEventRecord(stop);

	cudaEventSynchronize(stop);

	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

    	// Copy array back to host
    	cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
 
    	// Sum up vector c and print result divided by n, this should equal 1 within error
   	// double sum = 0;
   	// for(i=0; i<n; i++)
   	//     sum += h_c[i];
   	// printf("final result: %f\n", sum/n);
 
    	// Release device memory
    	cudaFree(d_a);
    	//cudaFree(d_b);
    	cudaFree(d_c);
 
	fprintf(fptr, "%ld %lf\n", n, milliseconds);
//	printf("%ld %lf\n", n, milliseconds);
    	// Release host memory
    	free(h_a);
    	//free(h_b);
    	free(h_c);
 	}
	fclose(fptr);
    	return 0;
}
