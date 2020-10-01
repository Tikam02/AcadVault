#include<stdio.h>
#include<cuda.h>

int main()

{

    int devCount;

    cudaGetDeviceCount(&devCount);

    printf("CUDA Device Query...\n");

    printf("There are %d CUDA devices.\n", devCount);

 
    for (int i = 0; i < devCount; ++i)
    {

        // Get device properties

        printf("\nCUDA Device #%d\n", i);

        cudaDeviceProp devProp;

        cudaGetDeviceProperties(&devProp, i);

        printf("Device Name: %s\n", devProp.name);
        printf("Total Global Memory: %d\n", devProp.totalGlobalMem);
		printf("Maximum Threads per Block: %d\n", devProp.maxThreadsPerBlock);
		printf("Maximum Threads Dimension in X-axis: %d\n", devProp.maxThreadsDim[0]);
		printf("Maximum Threads Dimension in Y-axis: %d\n", devProp.maxThreadsDim[1]);
		printf("Maximum Threads Dimension in Z-axis: %d\n", devProp.maxThreadsDim[2]);
		printf("Maximum Grid Size in X-axis: %d\n", devProp.maxGridSize[0]);
		printf("Maximum Grid Size in Y-axis: %d\n", devProp.maxGridSize[1]);
		printf("Maximum Grid Size in Z-axis: %d\n", devProp.maxGridSize[2]);
		printf("Warp Size: %d\n", devProp.warpSize);
		printf("Clock Rate: %d\n", devProp.clockRate);
	printf("Shared Memory Per Block: %d\n", devProp.sharedMemPerBlock);
	printf("Registers Per Block: %d\n", devProp.regsPerBlock);
	//printf("");
    }

    return 0;

}
