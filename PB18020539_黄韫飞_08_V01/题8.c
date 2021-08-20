/*
计算物理作业第八题 PB18020539 黄韫飞
用Monte-Carlo方法计算如下定积分，并讨论有效数字位数
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//产生随机数
static double I;
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
double RandGen() {
	static int a = 16807, b = 0, m = 2147483647;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
double func1(double x) {
	return sqrt(x + sqrt(x));
}
//平均值法积分
double quad1(int N) {
	int i = 0;
	double x;
	double sum=0;
	for (i = 0; i < N; i++) {
		x = RandGen()*2;
		sum += func1(x);
	}
	return (double)2 / N * sum;
}
double quad2(int N) {
	double x, y, z, u, v;
	double sum=0;
	int i;
	for (i = 0; i < N; i++) {
		x = RandGen()*9.0 / 10;
		y = RandGen()*4.0 / 5;
		z = RandGen()*9.0 / 10;
		u = RandGen() * 2;
		v = RandGen()*13.0 / 10;
		sum += 6 - pow(x, 2) - pow(y, 2) - pow(z, 2) - pow(u, 2) - pow(v, 2);
	}
	return 9.0 / 10 * 4.0 / 5 * 9.0 / 10 * 2 * 13.0 / 10 / N * sum;
}
void DoQuadl1(int n) {
	int N = 0, i = 0, j = 0;
	double sigmas = 0;
	printf("quad1\n");
	for (i = 3; i < 7; i++) {
		double avg = 0, avgsqr = 0;
		//avg是n次积分值的平均，avgsqr是n次积分值平方的平均，这两个数用于求积分值的标准差sigma_s
		N = pow(10, i);
		I = (double)rand();//随机设定一个种子
		for (j = 0; j < n; j++) {
			double quad = quad1(N);
			avg += quad;
			avgsqr += (quad * quad);
		}
		avg /= n;
		avgsqr /= n;
		printf("N:%d\nquad=%.8lf\n", N, avg);
		sigmas = sqrt(avgsqr - avg * avg);
		printf("sigmas=%.8lf\n", sigmas);
	}
}
void DOQuadl2(int n) {
	int N = 0, i = 0, j = 0;
	double sigmas = 0;
	printf("quad2\n");
	for (i = 3; i < 7; i++) {
		double avg = 0, avgsqr = 0;
		N = pow(10, i);
		I = (double)rand();//随机设定一个种子
		for (j = 0; j < n; j++) {
			double quad = quad2(N);
			avg += quad;
			avgsqr += (quad * quad);
		}
		avg /= n;
		avgsqr /= n;
		printf("N:%d\nquad=%.8lf\n", N, avg);
		sigmas = sqrt(avgsqr - avg * avg);
		printf("sigmas=%.8lf\n", sigmas);
	}
}

int main() {
	srand((unsigned)time(NULL));
	int n = 100;
	DoQuadl1(n);
	DOQuadl2(n);
}
