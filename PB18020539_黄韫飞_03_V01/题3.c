/*
����������ҵ ��3�� PB18020539 ��蹷�
��������ϵ(\rho,\theta,\phi)�²��������Ͼ��ȷֲ�����������
������ֱ�ӳ�������
*/
#define Pi 3.14159
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//��16807���������������[0,1]�ϵľ��������
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
//�������Ͼ��ȳ���
int main() {
	FILE *fp1;
	if ((fp1 = fopen("RandSphere.txt", "w")) == NULL) {
		printf("ERROR, Failed to open the file.");
		exit(0);
	}
	double phi,t,theta;
	int i = 0, N = 5E3;
	for (i = 0; i < N; i++) {
		phi = 2 * Pi*RandGen16807();
		t = 2 * RandGen16807() - 1;
		theta = acos(t);
		/*theta = Pi * RandGen16807();*///�������������theta���ȷֲ������
		fprintf(fp1, "%lf\t%lf\n", theta,phi);
	}
	printf("done!\n"); 
	fclose(fp1);
	return 0;
}
