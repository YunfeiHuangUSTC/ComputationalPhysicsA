/*
计算物理作业题13 PB18020539 黄韫飞
用Metropolis-Hasting方法计算积分
*/
#define MIN(a,b) ((a<=b)?a:b)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//随机数产生器
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
//积分
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
	printf("Υ=%lf\t积分结果：%lf\t抽样效率：%lf\n", gamma,avg,eff);
	return avg;
}
int main() {
	int N=1E6;
	double gamma;
	printf("积分1：\n");
	for(gamma=2;gamma<=10;gamma+=0.5){
		Quadl1(N,gamma);
	}
}
