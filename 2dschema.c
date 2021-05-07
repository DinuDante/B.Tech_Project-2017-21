#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define m 5
#define n 5
#define alpha 0.0001
#define ko 385.0

int main()
{
	int i,j,c;
	float a=0.0, b=0.1, dx,error,dt,kh1,kh2;
	float x[m][n], T[m][n], Tj[m][n], k[n][m];
	
	FILE *f1;
	f1 = fopen("2d_v1.dat", "w");
	
	dx = (b-a)/(n-1);
	dt=(0.25*dx*dx)/alpha;
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			x[i][j] = a + dx*j;
			T[i][j] = 30.0;
		}
	}
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if((i==0 && j<n) || (i==n-1 && j<n))
			{
				T[i][j] = 200.0;
			}
			else if((j==0 && i<n) || (j==n-1 && i<n))
			{
				T[i][j] = 100.0;
			}
		}
	}
	T[0][0]=T[0][n-1]=T[n-1][0]=T[n-1][n-1]=200.0;
	
	//Printing 2d Array
	printf("The initial Array is :\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%f\t",T[i][j]);
		}
		printf("\n");
	}
}
