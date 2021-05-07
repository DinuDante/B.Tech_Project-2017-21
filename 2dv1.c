#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n 101
#define m 101
#define alpha 0.001

int main()
{
	int i,j,c,iter;
	float a=0.0, b=0.1, dx, dy, error, dt, TDummy;
	float x[m][n], T[m][n], y[m][n];
	
	FILE *f1;
	f1 = fopen("2d.dat", "w");
	
	dx = (b-a)/(n-1);
	dy = (b-a)/(m-1);
	dt=(0.25*dx*dx)/alpha;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			x[i][j] = a + dx*i;
			y[i][j] = a + dy*j;
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
	printf("The Initial Array :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%f\t",T[i][j]);
		}
		printf("\n");
	}
	
	for(iter=0;iter=100000;iter++)
	{
		error = 0.0;
		for(i=1;i<n-1;i++)
		{
			for(j=1;j<m-1;j++)
			{
				TDummy = T[i][j];
				T[i][j] = 0.25*(T[i][j-1] + T[i-1][j] + T[i+1][j] + T[i][j+1]);
				error = error + (T[i][j] - TDummy)*(T[i][j] - TDummy);
			}
		}
		error = error/(n-2);
		//printf("Error Final = %f\n", error);
		
		if(error<1.0E-6)
			break;
		
	}
	
	printf("The Final Array :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			fprintf(f1,"%f\t%f\t%f\n", x[i][j], y[i][j], T[i][j]);
			printf("%f\t",T[i][j]);
		}
		printf("\n");
		fprintf(f1,"\n");
	}
	
}
