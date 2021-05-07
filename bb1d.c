#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define alpha 0.0001

#define n 100

void main()
{
	int i,j, iter;
	float a = -1.0, b = 1.0, c = -0.1, dx, dt, Udummy, error, t=0.0;
	float u[n], ud[n], x[n];

	FILE *f1;
	f1 = fopen("h.dat", "w");

	dx = (b-a)/(n-1);
	dt=(dx*0.25)/(c);
	//printf("dx=%f\n", dx);
	
	for(i=0;i<n;i++)
	{
		x[i] = a + dx*i;
		
		if(i>=(n/3) && i<(2*n)/3)
		{
			u[i]=1;
		}
		else
		{
			u[i]=-1;
		}
	}

	for(iter=0;iter<1000000;iter++)
	{
		t = t+dt;
		error = 0.0;
		
		
		for(i=1;i<n;i++)
		{
			//ud[i] = u[i] - (c * dt * (u[i+1]-u[i])/dx);
			ud[i] = u[i] - ((c * dt * (u[i]-u[i-1]))/dx);
			//ud[i] = u[i] - (c * dt * (u[i+1]-u[i-1])/dx);
		}
		
		for(i=1;i<n;i++)
		{
			u[i]=ud[i];
		}

		error =error/(n-2);
		//printf("Error Final=%f\n", error);

		if(abs(t)>=3)
			break;
	}
	for(i=0;i<n;i++)
	{
		fprintf(f1,"%f\t%f\n", x[i], u[i]);
		
		printf("%f\t%f\n", x[i], u[i]);
	}
}

