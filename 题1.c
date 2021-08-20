/*
����������ҵ ��һ�� PB18020539 ��蹷�
��Scarge������д������ӳ��������������������Ϊ�������ֵ������ɸ����ƽ��ֲ�ͼ��
����<x^k>���Ծ����ԣ���ȡ��ͬ����Nֵ������ƫ����N�Ĺ�ϵ����C(l)�������ά������
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Scrage�Զ�ȡmod
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}

//RandGen16807��16807�����������
double RandGen16807() {
	static int I = 1, a = 16807, b = 0, m = 2147483647;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}

int main() {
	/*FILE *fp1;
	if ((fp1 = fopen("RandGen16807.txt", "w")) == NULL) {
		printf("ERROR, Failed to open the file.");
		exit(0);
	}*/
	int N =1E7, i = 0;
	double RandNum = 0;
	double *RandArr = (double *)malloc(N * sizeof(double));
	double Xk[15];
	double avg = 0;
	//����16807������
	for (i = 0; i < N; i++)
	{
		RandNum = RandGen16807();
		//�������д���ļ�
		/*if(i%2==0)
		    fprintf(fp1, "%lf\t", RandNum);
		else
			fprintf(fp1, "%lf\n", RandNum);*/
		RandArr[i] = RandNum;
	}
	/*fclose(fp1);*/
	//����x^k��ƽ��ֵ
	int k,l; 
	for (k = 1; k <= 10; k++)
	{
		for (i = 0; i < N; i++) {
			avg += pow(RandArr[i], k);
		}
		avg /= N;
		Xk[k] = avg;
		printf("k=%d,x^k=%lf,1/(1+k)=%lf\n", k, Xk[k],(double)1/(1+k));
		printf("delta=%lf\n", Xk[k]-(double)1 / (1 + k));
	}
	//C(l)���Զ�ά������
	double Avg_l = 0, C_l = 0;
	for (l = 1; l < 10; l++)
	{
		for (i = 0; i < N - l; i++) {
			Avg_l += RandArr[i] * RandArr[i + l];
		}
		Avg_l /= (N - l);
		C_l = (Avg_l - Xk[1] * Xk[1]) / (Xk[2] - Xk[1] * Xk[1]);
		printf("l=%d,C_l=%lf\n", l, C_l);
	}
	return 0;
}
