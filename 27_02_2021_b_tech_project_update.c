#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n 101
#define alpha 0.0000231

int main()
{
	int i,j,count=0,num;
	float a=0.0, b=0.1, dx,error,dt;
	float T[n],x[n],Tj[n];
	
	FILE *f1;
	f1 = fopen("b.dat", "w");
	
	dx = (b-a)/(n-1);
	dt=(0.25*dx*dx)/alpha;
	//printf("%f \n",dt);
	
	for(i=0;i<n;i++)
	{
		x[i] = a + dx*i;
		T[i]=30.0;
	}
	for(j=1;j<1000000;j++)
	{
        	count++;
		T[0]=200.0;
		T[n-1] = 40.0;
	
	
		for(i=1;i<n-1;i++)
		{
			Tj[i]=T[i]+(alpha*dt)*(T[i+1]-(2*T[i])+T[i-1])/(dx*dx);
		}
		Tj[0]=200;
		Tj[n-1]=40;
	    error=0.0;
		for(i=0;i<n;i++)
		{
			error=error+(Tj[i]-T[i])*(Tj[i]-T[i]);
		}
		error=sqrtf(error/n);
    	for(i=0;i<n;i++)
		{
			T[i]=Tj[i];
		}
		if(error<1.0E-16)
			break;
	num=10/dt;
	if(j%num==0)
	{
		for(i=0;i<n;i++)
		{
			printf("%f\t %f\t %f\n",x[i],T[i],Tj[i]);
			fprintf(f1,"%f\t%f\n", x[i], T[i]);
		}
	}
	}
	for(i=0;i<n;i++)
	{
		printf("%f\t %f\t %f\n",x[i],T[i],Tj[i]);
		fprintf(f1,"%f\t%f\n", x[i], T[i]);
	}
}
