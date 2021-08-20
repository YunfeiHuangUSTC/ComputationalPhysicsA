/*
计算物理作业 第二题 PB18020539 黄韫飞
用16807产生器测试随机数序列中满足X_n-1<X_n+1<X_n的比重。
讨论Fibonacci延迟产生器中出现这种关系的比重。
*/
#define MAX(p,q) ((p>q)?p:q)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//使用了作业题1中的16807产生器，定义全局变量
static int a = 16807, b = 0, m = 2147483647;
//SchrageMethod：自动取mod
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
//RandGen16807：16807随机数产生器
double RandGen16807() {
	static int I = 1;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
//Fibonacci延迟产生器
double FiboGen() {
	static int p = 0xC8,q=0x98;
	static long long int a[500];
	//因为p和q可以表示的最大数是16^2-1=255，取500可以保证操作在数组范围内
	//另外，发现如果不用long long，会有溢出现象
	static int n = 0,firsttime=1;
	int i;
	//对前MAX(p,q)个数进行初始化，只在第一次执行
	if (firsttime) {
		n = MAX(p, q);
		for (i = 0; i<=n; i++)
		{
			a[i] = RandGen16807()*m;
		}
		firsttime = 0;
	}
	n = (n + 1) % 500;
	a[n] = (a[(n - p + 500) % 500] + a[(n - q + 500) % 500]) % m;//括号内+500防止出现负数
	return a[n] / (double)m;
}
int main() {
	int Count1 = 0,Count2=0;//计数变量
	int N = 2E7, i = 0,j=0;
	float Prop1,Prop2;
	double *RandArr = (double *)malloc(N * sizeof(double));
	//讨论16807产生器中X_n-1<X_n+1<X_n的比重
	for (i = 0; i < N; i++) {
		RandArr[i] = RandGen16807();
	}
	for (j = 1; j < N - 1; j++) {
		if (RandArr[j - 1] < RandArr[j + 1] && RandArr[j + 1] < RandArr[j]) {
			Count1++;
		}
	}
	Prop1 = (float)Count1 / N;
	printf("proportion of relationship Xn-1<Xn+1<Xn is:\n");
	printf("Gen16807: %f\n", Prop1);
	//讨论Fibonacci延迟产生器中X_n-1<X_n+1<X_n的比重
	for (i = 0; i < N; i++) {
		RandArr[i] = FiboGen();
	}
	for (j = 1; j < N - 1; j++) {
		if (RandArr[j - 1] < RandArr[j + 1] && RandArr[j + 1] < RandArr[j]) {
			Count2++;
		}
	}
	Prop2 = (float)Count2 / N;
	printf("proportion of relationship Xn-1<Xn+1<Xn is:\n");
	printf("Fibonacci:%f\n", Prop2);
	return 0;
}
