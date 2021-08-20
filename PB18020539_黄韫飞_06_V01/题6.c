/*
计算物理作业 第6题 PB18020539 黄韫飞
对两个函数线型（Gauss分布和类Lorentz型分布），设其一为p(x)，另一为F(x)，用舍选法对p(x)抽样。
将计算得到的归一化频数分布直方图与理论曲线p(x)进行比较，讨论差异。讨论抽样效率。
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//定义全局变量
double A = 0.398943;
double B = 0.95;
//定义p和F
double p(double x) {
	return A * exp(-x * x / 2);
}
double F(double x) {
	return B / (1 + pow(x, 4));
}
//定义概率分布函数G
double Phi(double x) {
	return B / (4 * sqrt(2))*(log((x*x + sqrt(2)*x + 1) / (x*x - sqrt(2)*x + 1)) + \
		2 * (atan(1 + sqrt(2)*x) - atan(1 - sqrt(2)*x)));
}
double G(double x) {
	return Phi(x) - Phi(-5);
}
//生成随机数，直接调用了C语言中的rand函数
double RandGen() {
	return (double)rand() / RAND_MAX;
}
//用二分法求G的反函数
double GInvFunc(double g) {
	double l = -5, r = 5, m = 0;
	double accu = 1e-5;
	while (r - l > accu) {
		m = (l + r) / 2;
		if (G(m) > g)
			r = m;
		else l = m;
	}
	return m;
}
int main() {
	FILE *fp1;
	if ((fp1 = fopen("SelSamp.txt", "w")) == NULL) {
		printf("Fail to Open the File\n");
		exit(0);
	}
	int i, N = 1E4;
	double xi1, xi2, xix, xiy;
	int Count1=0;
	for (i = 0; i < N;i++) {
		xi1 = RandGen();
		xi2 = RandGen();
		xix = GInvFunc(G(5)*xi1);
		xiy = xi2 * F(xix);
		if (xiy < p(xix)) {
			Count1++;
			fprintf(fp1, "%lf\t%lf\n", xix, xiy);
		}
	}
	fclose(fp1);
	printf("产生%d组，有效%d组，效率:%lf\n", N, Count1, (double)Count1 / N);
}
