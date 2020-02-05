#include <stdio.h>
#include <omp.h>
#include <math.h>

int main()
{
	int N = 256, maxN = pow(2, 10);
	for(N = 2; N<256; N*=2)
	{
		double mat[N][N], s[N][N], val;
		int i, j, v[N];
		for(i=0; i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				s[i][j] = i+1*j;
			}
			v[i] = i;
		}
		double startTime = omp_get_wtime();
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				
				val = (double) (v[i]%256);	
				mat[j][i] = s[j][i]* (sin(val)*sin(val) - cos(val)*cos(val));
			}
		}
		double endTime = omp_get_wtime() - startTime;
		
		double throughput = (sizeof(double) * 8 * N) / (double) endTime;
		printf("%lf %d\n", throughput, N);
	}

	for(N = 2; N<256; N*=2)
	{
		double mat[N][N], s[N][N], val;
		int i, j, v[N];
		for(i=0; i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				s[i][j] = i+1*j;
			}
			v[i] = i;
		}
		double startTime = omp_get_wtime();
		for(i=0;i<N;i++)
		{
			val = (double) (v[i]%256);
			double sv = sin(val);
			double cv = cos(val);	
			for(j=0;j<N;j++)
			{
				mat[i][j] = s[i][j] * (sv*sv - cv*cv);
			}
		}
		double endTime = omp_get_wtime() - startTime;
		
		double throughput = (sizeof(double) * 8 * N) / (double) endTime;
		printf("%lf %d\n", throughput, N);
	}
	return 0;
}
