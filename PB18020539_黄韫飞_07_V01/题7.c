/*
计算物理作业第七题 PB18020539 黄韫飞
对一个实验谱数值曲线p(x)，自设F(x)，分别用直接抽样和舍选法对p(x)抽样。
比较原曲线和抽样得到的曲线以验证，讨论抽样效率
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
int p[114];
int E[114];
int n = 114;
int N = 1E6;
//产生[0,1]区间的随机数
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
//定义F(x)和G(x)
double F(double x) {
	if (x>=2900&&x<=2990) {
		return 5672;
	}
	else return 37630;
}
double G(double x) {
	if (x >= 2900 && x <= 2990) {
		return 5672*(x-2900);
	}
	else return 510480 + 37630 * (x - 2990);
}
//求G(x)的反函数
double GInverse(double g) {
	if (g >= 0 && g <= 510480) {
		return g / 5672 + 2900;
	}
	else return 2990 + (g - 510480) / 37630;
}
//将数据输入
int DataInput() {
	FILE *fp1;
	if ((fp1 = fopen("data.TXT", "r")) == NULL) {
		printf("Open Failed\n");
		exit(0);
	}
	char s[100];
	fgets(s, 50, fp1);
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		fscanf(fp1, "%d", &E[i]);
		fscanf(fp1, "%d", &p[i]);
		//printf("%d\t%d\n", E[i], p[i]);
	}
	fclose(fp1);
}
//p(x)
double px(double x) {
	int i = 0;
	for (i = 0; i < n; i++) {
		if((E[i] <= x && E[i + 1] > x)) {
			return p[i];
		}
	}
}
int main() {
	FILE *fp2, *fp3;
	if ((fp2 = fopen("Sample1.txt", "w")) == NULL) {
		printf("Open Failed\n");
		exit(0);
	}
	if ((fp3 = fopen("Sample2.txt", "w")) == NULL) {
		printf("Open Failed\n");
		exit(0);
	}
	double xi1, xi2, xix, xiy;
	int i = 0, Count1 = 0, Count2 = 0;
	DataInput();
	//直接抽样
	for (i = 0; i < N; i++) {
		xix = 2900 + 113 * RandGen();
		xiy = 37630 * RandGen();
		if (xiy <= px(xix)) {
			Count1++;
			fprintf(fp2, "%lf\t%lf\n", xix, xiy);
		}
	}
	printf("直接抽样：抽样点%d个，有效点%d个，效率%.2f%%\n", N, Count1, (float)Count1 / N * 100);
	//舍选法抽样
	for (i = 0; i < N; i++) {
		xi1 = RandGen();
		xi2 = RandGen();
		xix = GInverse(xi1*G(3013));
		xiy = xi2 * F(xix);
		if (xiy < px(xix)) {
			Count2++;
			fprintf(fp3, "%lf\t%lf\n", xix, xiy);
		}
	}
	printf("舍选法：抽样点%d个，有效点%d个，效率%.2f%%\n", N, Count2, (float)Count2 / N * 100);
}
