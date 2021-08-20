/*
计算物理作业第九题 PB18020539 黄韫飞
自设若干个随机分布（相同或不同的\mu 和\sigma^2）
通过Monte Carlo模拟，验证中心极限定理成立(N=2,5,10)
*/
#define Pi 3.1415926
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int N = 10;
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
//分布1：正态分布N(0,1)
double function1() {
	double u, v;
	u = RandGen();
	v = RandGen();
	return sqrt(-2 * log(u))*cos(2 * Pi*v);
}
void Sample1() {
	FILE *fp1;
	if ((fp1 = fopen("data1.txt", "w")) == NULL) {
		printf("Open Failed!\n");
		exit(0);
	}
	int m = 1E4;
	int i = 0, j = 0;
	double f, sigmaf, samp1;
	for (j = 0; j < m; j++) {
		double avg = 0, avgsqr = 0;
		for (i = 0; i < N; i++) {
			f = function1();
			avg += f;
			avgsqr += f * f;
		}
		avg /= N;
		avgsqr /= N;
		sigmaf = sqrt(avgsqr - avg * avg);
		samp1 = avg * sqrt(N) / sigmaf;
		fprintf(fp1, "%lf\n", samp1);
	}
	fclose(fp1);
	printf("1 done!\n");
}
double function2() {
	double xi;
	xi = RandGen();
	return -2 * log(xi);
}
void Sample2() {
	FILE *fp2;
	if ((fp2 = fopen("data2.txt", "w")) == NULL) {
		printf("Open Failed!\n");
		exit(0);
	}
	int m = 1E4;
	int i = 0, j = 0;
	double f, sigmaf, samp2;
	for (j = 0; j < m; j++) {
		double avg = 0, avgsqr = 0;
		for (i = 0; i < N; i++) {
			f = function2();
			avg += f;
			avgsqr += f * f;
		}
		avg /= N;
		avgsqr /= N;
		sigmaf = sqrt(avgsqr - avg * avg);
		samp2 = (avg-2) * sqrt(N) / sigmaf;
		fprintf(fp2, "%lf\n", samp2);
	}
	fclose(fp2);
	printf("2 done!\n");
}
int main() {
	Sample1();
	Sample2();
}