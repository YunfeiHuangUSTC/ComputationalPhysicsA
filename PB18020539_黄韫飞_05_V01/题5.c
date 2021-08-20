/*
����������ҵ ��5�� PB18020539 ��蹷�
���������Ͼ��ȷֲ����������㣬����������(x,y)ƽ����ͶӰ�ļ��ʷֲ�������
���ɴ���֤Marsaglia������x=2u\sqrt{1-r^2},y=2v\sqrt{1-r^2},z=1-2r^2ȷΪ�����Ͼ��ȷֲ����������
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//��Schrage������16807����������[0,1]�ϵ������
static int a = 16807, b = 0, m = 2147483647;
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
double RandGen16807() {
	static int I = 1;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
//����������
int main() {
	FILE *fp1;
	if((fp1 = fopen("RandSphere.txt", "w")) == NULL) {
		printf("ERROR, Failed to open the file.");
		exit(0);
	}
	double u, v, r,x,y,z;
	int N = 1E4, i = 0;
	for (i = 0; i < N; i++) {
generate:		u = 2*RandGen16807()-1;
		v = 2*RandGen16807()-1;
		r = sqrt(u*u + v * v);
		if (r > 1) goto generate;
		x = 2 * u*sqrt(1 - r * r);
		y = 2 * v*sqrt(1 - r * r);
		z = 1 - 2 * r*r;
		fprintf(fp1, "%f %f %f\n", x, y,z);
	}
	printf("done!\n"); 
	fclose(fp1);
}
