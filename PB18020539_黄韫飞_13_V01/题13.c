/*
����������ҵ��13 PB18020539 ��蹷�
��Metropolis-Hasting�����������
*/
#define MIN(a,b) ((a<=b)?a:b)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//�����������
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
double RandGen() {
	static int I = 20, a = 16807, b = 0, m = 2147483647;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
//����
double Quadl1(double N,double gamma) {
	double x=1,xp,r,avg=0,eff;
	int i,Count=0;
	for(i=0;i<N;i++){
		xp=-gamma*log(RandGen());
		r=(xp/x)*exp(x-xp)*exp((xp-x)/gamma);
		if (RandGen()<MIN(1,r)) {
			x=xp;
			Count++;
		}
		avg+=(x-2)*(x-2);
	}
	avg/=N;
	eff=Count/N;
	printf("��=%lf\t���ֽ����%lf\t����Ч�ʣ�%lf\n", gamma,avg,eff);
	return avg;
}
int main() {
	int N=1E6;
	double gamma;
	printf("����1��\n");
	for(gamma=2;gamma<=10;gamma+=0.5){
		Quadl1(N,gamma);
	}
}
