/*
����������ҵ �ڶ��� PB18020539 ��蹷�
��16807�������������������������X_n-1<X_n+1<X_n�ı��ء�
����Fibonacci�ӳٲ������г������ֹ�ϵ�ı��ء�
*/
#define MAX(p,q) ((p>q)?p:q)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//ʹ������ҵ��1�е�16807������������ȫ�ֱ���
static int a = 16807, b = 0, m = 2147483647;
//SchrageMethod���Զ�ȡmod
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
//RandGen16807��16807�����������
double RandGen16807() {
	static int I = 1;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
//Fibonacci�ӳٲ�����
double FiboGen() {
	static int p = 0xC8,q=0x98;
	static long long int a[500];
	//��Ϊp��q���Ա�ʾ���������16^2-1=255��ȡ500���Ա�֤���������鷶Χ��
	//���⣬�����������long long�������������
	static int n = 0,firsttime=1;
	int i;
	//��ǰMAX(p,q)�������г�ʼ����ֻ�ڵ�һ��ִ��
	if (firsttime) {
		n = MAX(p, q);
		for (i = 0; i<=n; i++)
		{
			a[i] = RandGen16807()*m;
		}
		firsttime = 0;
	}
	n = (n + 1) % 500;
	a[n] = (a[(n - p + 500) % 500] + a[(n - q + 500) % 500]) % m;//������+500��ֹ���ָ���
	return a[n] / (double)m;
}
int main() {
	int Count1 = 0,Count2=0;//��������
	int N = 2E7, i = 0,j=0;
	float Prop1,Prop2;
	double *RandArr = (double *)malloc(N * sizeof(double));
	//����16807��������X_n-1<X_n+1<X_n�ı���
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
	//����Fibonacci�ӳٲ�������X_n-1<X_n+1<X_n�ı���
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
