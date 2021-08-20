/*
����������ҵ ��6�� PB18020539 ��蹷�
�������������ͣ�Gauss�ֲ�����Lorentz�ͷֲ���������һΪp(x)����һΪF(x)������ѡ����p(x)������
������õ��Ĺ�һ��Ƶ���ֲ�ֱ��ͼ����������p(x)���бȽϣ����۲��졣���۳���Ч�ʡ�
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//����ȫ�ֱ���
double A = 0.398943;
double B = 0.95;
//����p��F
double p(double x) {
	return A * exp(-x * x / 2);
}
double F(double x) {
	return B / (1 + pow(x, 4));
}
//������ʷֲ�����G
double Phi(double x) {
	return B / (4 * sqrt(2))*(log((x*x + sqrt(2)*x + 1) / (x*x - sqrt(2)*x + 1)) + \
		2 * (atan(1 + sqrt(2)*x) - atan(1 - sqrt(2)*x)));
}
double G(double x) {
	return Phi(x) - Phi(-5);
}
//�����������ֱ�ӵ�����C�����е�rand����
double RandGen() {
	return (double)rand() / RAND_MAX;
}
//�ö��ַ���G�ķ�����
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
	printf("����%d�飬��Ч%d�飬Ч��:%lf\n", N, Count1, (double)Count1 / N);
}
