#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define n 101
#define alpha 0.0001
#define ko 385.0
#define ak 0.1

int main()
{
	int i,j,count=0,num;
	float a=0.0, b=0.1, dx,error,dt,kh1,kh2;
	float T[n],x[n],Tj[n],k[n];
	
	FILE *f1;
	f1 = fopen("g.dat", "w");
	
	dx = (b-a)/(n-1);
	dt=(0.25*dx*dx)/alpha;
	//printf("%f \n",dt);
	
	for(i=0;i<n;i++)
	{
		x[i] = a + dx*i;
		T[i]=30.0;
	}
	T[0]=200.0;
	T[n-1] = 40.0;
	

	
	for(j=1;j<100000;j++)
	{	
		for(i=0;i<n;i++)
		{
			k[i]=ko*(1+(ak*sin(x[i])))*(1+(alpha*T[i]));
			//printf("k=%f\n",k[i]);		
		}
	    error=0.0;
	
	
		for(i=1;i<n-1;i++)
		{
			kh1=(k[i]+k[i+1])/2.0;

			kh2=(k[i]+k[i-1])/2.0;
			
			//printf("kh1=%f\t kh2=%f\n",kh1,kh2);
			
			Tj[i]=((kh1*T[i+1])+(kh2*T[i-1]))/(kh1+kh2);
		}
		Tj[0]=200;
		Tj[n-1]=40;
	    error=0.0;
		for(i=1;i<n-1;i++)
		{
			error=error+(Tj[i]-T[i])*(Tj[i]-T[i]);
		}
		error=sqrtf(error/n);
    	for(i=1;i<n;i++)
		{
			T[i]=Tj[i];
		}
		if(error<1.0E-16)
			break;
	num=10/dt;
	}
	for(i=0;i<n;i++)
	{
		printf("%f\t %f\t %f\t %f\n",x[i],T[i],Tj[i],k[i]);
		fprintf(f1,"%f\t%f\n", x[i], T[i]);
	}
}
