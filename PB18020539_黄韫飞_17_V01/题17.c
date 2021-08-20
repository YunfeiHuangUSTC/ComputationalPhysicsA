/*
PB18020539 ��蹷� ����������ҵ��ʮ���� 
*/ 
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.14159
FILE *fp;
//����M+N�Σ�����ΪM��֮����Դﵽ�ȶ�״̬��ȡM�ε���֮���N�λ�ͼ 
void chaos(int M,int N,double lambda){
	int i;
	double xnew,xold=0.6;
	for(i=0;i<M;i++){
		xnew=lambda*sin(PI*xold);
		xold=xnew;
	}
	for(i=0;i<N;i++){
		xnew=lambda*sin(PI*xold);
		xold=xnew;
		fprintf(fp,"%lf\t%lf\n",lambda,xnew);
	}
}
void main(){
	double lmax,lmin,lstep,lambda;
	lmax=1.5;
	lmin=0;
	lstep=2e-4;
	int M,N;
	M=200;
	N=100;
	if((fp=fopen("Data.txt","w"))==NULL){
		printf("ERROR\n");
		exit(0);
	}
	for(lambda=lmin;lambda<=lmax;lambda+=lstep){
		chaos(M,N,lambda);		
	}
	fclose(fp);
}
 
