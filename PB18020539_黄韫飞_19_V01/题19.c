/*
计算物理作业第十九题	PB18020539	黄韫飞 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.1415926
double n=1E5,a=0,b=1;
double h;
double Psi(double E){
	double *psi;
	int i;
	psi=(double *)malloc((int)n*sizeof(double));
	psi[0]=0;
	psi[1]=sqrt(2)*sin(sqrt(E)*h);
	for(i=2;i<n;i++){
		psi[i]=(2*(1-5*h*h*E/12)*psi[i-1]-(1+h*h*E/12)*psi[i-2])/(1+h*h*E/12);
	}
	return psi[(int)n-1];
}
int main(){
	h=(b-a)/(n-1);
	double E,E1,E2,Enew,tolE=1e-5;
	int mark=0;
	for(E=5;E<300;E=E+5){
		mark=0;
		E1=E;E2=E+5;
		while((Psi(E1)*Psi(E2)<0)&&fabs(E2-E1)>tolE){
			Enew=(E1+E2)/2;
			if(Psi(Enew)*Psi(E1)<0){
				E2=Enew;
			}
			else E1=Enew;
			mark=1;
		}
		if(mark=1){
			printf("E=%lf\n",Enew);
		}
	}
} 
