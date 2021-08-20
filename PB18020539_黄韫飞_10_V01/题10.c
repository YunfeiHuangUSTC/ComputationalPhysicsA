/*
计算物理作业第十题 PB18020539 黄韫飞
Monte Carlo方法研究正弦力场 (~sin(\omega t))中的行走
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define N 1000 //粒子数，用于求平均值
double a = 0.3;//a表示的是正弦力场与涨落力的相对大小
double w = 0.2;
//随机数产生器
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
//行走函数
int RandWalk(int t,int x) {
	double judge;
	judge = RandGen();
	if (judge < 0.5 + a * sin(w * t)) {
		x++;
	}
	else x--;
	return x;
}
int main() {
	FILE *fp1, *fp2;
	if ((fp1 = fopen("x&xsqr.txt", "w")) == NULL) {
		printf("OPEN FAILED\n");
		exit(0);
	}
	if ((fp2 = fopen("Distri.txt", "w")) == NULL) {
		printf("OPEN FAILED\n");
		exit(0);
	}
	int i = 0;//第i个粒子
	int x[N];
	for (i = 0; i < N; i++) {
		x[i] = 0;
	}//初始位置在原点 
	int tmax = 300;
	int t = 0;
	double avgx = 0, avgsqr = 0;
	for (t = 0; t < tmax; t++) {
		for (i = 0; i < N; i++) {
			x[i]= RandWalk(t, x[i]);
			avgx += x[i];
			avgsqr += x[i] * x[i];
		}
		avgx /= N;
		avgsqr /= N;
		//求位移平均值 
		fprintf(fp1,"%lf\t%lf\n", avgx, avgsqr);
	}
	for (i = 0; i < N; i++){
		fprintf(fp2, "%d\n", x[i]);
	}
	fclose(fp1);
}
