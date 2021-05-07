#include"stdio.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define m 207
double dx,dt,lambda;
int main()
{
    int i,j,k,qq;
    double cpu_time;
    double d1=-10.0,d2=10.0,gamma=1.4,aa1,aa2,aa3,aa4,M_inf,aa11;
    double  t=0.0,M[m],delm1,delm2,bb1,bb2;
    double rho_le,rho_ri,p_l,p_r,v_l,s_v_l,v_r,s_v_r,en_le,en_ri;
    double cx[m],x[m],v[m],rho[m],s_v[m];
    double en[m], mv[m], p[m], rho0[m];
    double lambda_x1[m], rhox_5[m],mvx_5[m],enx_5[m];
    double mv_f[m],mv_p[m],mv_r[m],mv_n[m],mv_l[m],en_p[m],en_f[m],en_l[m],en_n[m],en_r[m];
    double rho_p[m],rho_n[m],rho_r[m],rho_l[m];

    double u_L_1, u_L_2, u_L_3, u_R_1, u_R_2, u_R_3, alpha_I_L, alpha_I_R, alpha_D_L, alpha_D_R, AI_AD_pre[m],AI_AD_post[m],u_ref;
    int num_int_wave_pre[m], num_div_wave_pre[m], num_int_wave_post[m], num_div_wave_post[m];
    double wave_int_max[m],wave_div_max[m],wave_int_min[m],wave_div_min[m];
    clock_t start, end;
    short int sign (double );
    FILE *x1,*x2;
    x1=fopen("llf_shock_100_1p.txt","w");
    x2=fopen("shock_wave_speed_100_1p.txt","w");

    double weno_1d(double , double *, double *, double *, double *, double *, double *);
    /*-------------- grid generation of the domain ----------------*/
    start = clock();

    dx=(d2-d1)/(m-7);

    for(i=3;i<m-3;i++)
    {
        x[i]=d1+(i-3)*dx;
    }
    for(i=3;i<m-3;i++)
    {
        cx[i]=x[i];//0.5*(x[i]+x[i+1]);
    }

    /*------------- intitial condition of the shock tube problem----------*/
    for(i=3;i<m-3;i++)
    {
        if(cx[i]<(0.5*(d2+d1)))
        {
            p[i]=1.0e5;
            rho[i]=1.0;
            v[i]=0.0;
            s_v[i]=sqrt(gamma*p[i]/rho[i]);
        }
        else 
        {
            p[i]=1.0e4;
            rho[i]=0.125;
            v[i]=0.0;
            s_v[i]=sqrt(gamma*p[i]/rho[i]);
        }

    }

    for(j=0;j<1000000;j++)
    {
        rho_le=rho[3];
        p_l=p[3];
        v_l=v[3];
        s_v_l=sqrt(gamma*p_l/rho_le);
        en_le=p_l/(gamma-1.0)+0.5*rho_le*v_l*v_l;

        rho_ri=rho[m-4];
        p_r=p[m-4];
        v_r=v[m-4];
        s_v_r=sqrt(gamma*p_r/rho_ri);
        en_ri = p_r/(gamma-1.0)+0.5*rho_ri*v_r*v_r;
        rho[m-3] = rho[m-4];
        v[m-3] = v[m-4];
        p[m-3] = p[m-4];
        s_v[m-3]=s_v[m-4];


        /*--------- Boundary condition of the 1-D Shock tube problem ----------*/ 
        lambda=0.0;
        for(i=3;i<m-3;i++)		
        {
            aa1=fabs(v[i])+s_v[i];
            if(lambda < aa1)
                lambda = aa1; 
        }
        dt=0.25*dx/lambda;
  
        for(i=3;i<m-2;i++)		
        {
            mv[i]=rho[i]*v[i];
            en[i]=p[i]/(gamma-1.0)+0.5*rho[i]*v[i]*v[i];
            M[i]=v[i]/s_v[i];
        }

        for(i=3;i<m-2;i++)		
        {
                lambda_x1[i]=fmax(fmax(fabs(v[i]),fabs(v[i+1])),fmax(s_v[i],s_v[i+1]));
        }

        for(i=3;i<m-4;i++)		
        {
            rhox_5[i]=0.5*(mv[i]+mv[i+1])-0.5*lambda_x1[i]*(rho[i+1]-rho[i]);
            mvx_5[i]=0.5*(mv[i]*v[i]+p[i]+mv[i+1]*v[i+1]+p[i+1])-0.5*lambda_x1[i]*(mv[i+1]-mv[i]);
            enx_5[i]=0.5*((en[i]+p[i])*v[i]+(en[i+1]+p[i+1])*v[i+1])-0.5*lambda_x1[i]*(en[i+1]-en[i]);
        }

        rhox_5[2]=rho_le*v_l;
        mvx_5[2]=rho_le*v_l*v_l+p_l;
        enx_5[2]=(p_l/(gamma-1.0)+0.5*rho_le*v_l*v_l+p_l)*v_l;

        rhox_5[m-4]=rho_ri*v_r;
        mvx_5[m-4]=rho_ri*v_r*v_r+p_r;
        enx_5[m-4]=(p_r/(gamma-1.0)+0.5*rho_ri*v_r*v_r+p_r)*v_r;   

        for(i=3;i<m-3;i++)		
        {
            rho[i]=rho[i]-dt*(rhox_5[i]-rhox_5[i-1])/dx;
            mv[i]=mv[i]-dt*(mvx_5[i]-mvx_5[i-1])/dx;
            en[i]=en[i]-dt*(enx_5[i]-enx_5[i-1])/dx;
            v[i]=mv[i]/rho[i];
            p[i]=(en[i]/rho[i]-0.5*v[i]*v[i])*rho[i]*(gamma-1.0);
            s_v[i]=sqrt(gamma*p[i]/rho[i]);
            M[i]=v[i]/s_v[i];
        }
        t=t+dt;
        		if (t>0.01)
        			break;
        printf("%f\n",t);
    }
    for(i=3;i<m-3;i++)
    { 
        fprintf(x1,"%f\t%f\t%f\t%f\t%f\t%f\n", cx[i],rho[i],v[i],p[i],s_v[i],M[i]);
    }
    end = clock();
    cpu_time= ((double)(end-start))/ (CLOCKS_PER_SEC);
    printf("%f\n",cpu_time);

    for(i=3;i<m-4;i++)
    { 
        fprintf(x2,"%f\t%f\t%f\t%f\t%d\t%d\t%d\t%d\n", x[i+1],lambda_x1[i],AI_AD_pre[i],AI_AD_post[i],num_int_wave_pre[i],num_div_wave_pre[i], num_int_wave_post[i], num_div_wave_post[i]);
    }
    return (0);
}
/*---------------subroutine to find the maximum of three numbers---------*/

