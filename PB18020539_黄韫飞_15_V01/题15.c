/*
PB18020539 ��蹷� ����������ҵ��15��
��Metropolis��������<x^2>,<y^2>,<x^2+y^2>����ͼ�������Markov�� 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define min(a,b) ((a<b)?a:b)
#define PI 3.14159
//�����������
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
double RandGen() {
	static int I = 1, a = 16807, b = 0, m = 2147483647;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
double prob(double x,double y,double sx,double sy){
	return 1/(2*PI*sx*sy)*exp(-(x*x/(2*sx*sx)+y*y/(2*sy*sy)));
} 
// ����
double Markov(double delta,double sx,double sy,double M,double N){
	FILE *fp;
	if((fp=fopen("Data.txt","w"))==NULL){
		exit(0);
	}
	double xold,xnew,yold,ynew,xt,yt,r;
	double x2=0,y2=0,x2y2=0;
	int i;
	xold=10;yold=10;
	fprintf(fp,"%lf\t%lf\n",xold,yold);
	for(i=0;i<M;i++){
		//������̽�� 
		xt=xold+delta*(RandGen()-0.5);
		yt=yold+delta*(RandGen()-0.5);
		r=prob(xt,yt,sx,sy)/prob(xold,yold,sx,sy);
		//��ѡ 
		if(RandGen()<min(1,r)){
			xnew=xt;
			xold=xnew;
			ynew=yt;
			yold=ynew; 
		}
		else{
			xnew=xold;
			ynew=yold;
		}
		fprintf(fp,"%lf\t%lf\n",xnew,ynew);
	}
	for(i=0;i<N;i++){
		xt=xold+delta*(RandGen()-0.5);
		yt=yold+delta*(RandGen()-0.5);
		r=prob(xt,yt,sx,sy)/prob(xold,yold,sx,sy);
		if(RandGen()<min(1,r)){
			xnew=xt;
			xold=xnew;
			ynew=yt;
			yold=ynew; 
			x2+=xnew*xnew;
			y2+=ynew*ynew;
		}
		else{
			xnew=xold;
			ynew=yold;
			x2+=xnew*xnew;
			y2+=ynew*ynew;
		}
	fprintf(fp,"%lf\t%lf\n",xnew,ynew);
	}
	x2/=N;
	y2/=N;
	x2y2=x2+y2;
	printf("x^2=%lf\n",x2);
	printf("y^2=%lf\n",y2);
	printf("x^2+y^2=%lf\n",x2y2);
} 
void main(){
	//�������
	double delta=0.5;//���� 
	double sx=2,sy=3;//���� 
	double M=5E5,N=1E6;//�ֱ����Ȼ�������ƽ��̬���߲��� 
	Markov(delta,sx,sy,M,N);
}
