#include<stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

//#define double long long
//#define ll long long
//#define N 100000000

struct timeval start, stop;

/*void vector_addition(double *a, double *b, double *c)
{
	double i;
	for(i=0; i<; i++)
	{
		c[i] = a[i] + b[i];
	}
}*/

double main()
{
	long long minSize = pow(2,8);
	long long maxSize = pow(2,28);
	//double cnt = 0;
	
//	double n = 20;
	
	long long size = minSize;
//	double throughput[n];
	
	FILE *fptr = fopen("serial_vector_add.txt", "w");
	
	for (size = minSize; size<maxSize; size*=2)
	{
		double *a = (double*)malloc(size*sizeof(double));
		double *b = (double*)malloc(size*sizeof(double));
		double *c = (double*)malloc(size*sizeof(double));
		long long i;
		for(i=0; i<size; i++)
		{
			a[i] = sin(i)*sin(i); 
			b[i] = cos(i)*cos(i);
		}

		double end_time;

		gettimeofday(&start,NULL);
		//double start_t = (stop.tv_sec)*1000000 + start.tv_usec;
	
		//vector_addition(a, b, c);
		for(i=0; i<size; i++)
        	{
                	c[i] = a[i] + b[i];
        	}
	
		gettimeofday(&stop,NULL);
		//double stop_t = (stop.tv_sec)*1000000 + stop.tv_usec;
		end_time = (stop.tv_sec - start.tv_sec)*1000000 + stop.tv_usec - start.tv_usec;	
	
	
//		throughput[cnt] = (sizeof(double) * 4 * size)/end_time;

		fprintf(fptr,"%ld %lf\n", size, end_time);
//		cnt++;	
	}
	fclose(fptr);	
	return 0;
}
