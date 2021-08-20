/*
计算物理作业题19-2 根据1中的结果，分别取E=9.869604，39.478426，88.826437，157.913675，246.740103 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	double n=1E5,a=0,b=1;
	double h=(b-a)/(n-1);
	double *psi,*x;
	double E=9.869604;
	int i=0;
	FILE *fp;
	if((fp=fopen("n=1.txt","w"))==NULL){
		printf("ERROR\n");
		exit(0);
	} 
	psi=(double *)malloc((int)n*sizeof(double));
	x=(double *)malloc((int)n*sizeof(double));
	for(i=0;i<n;i++){
		x[i]=i*h+a;
	}
	psi[0]=0;
	psi[1]=sqrt(2)*sin(sqrt(E)*h);
	for(i=2;i<n;i++){
		psi[i]=(2*(1-5*h*h*E/12)*psi[i-1]-(1+h*h*E/12)*psi[i-2])/(1+h*h*E/12);
	} 
	for(i=0;i<n;i++){
		fprintf(fp,"%lf\t%lf\n",x[i],psi[i]);
	}
	fclose(fp);
} 
