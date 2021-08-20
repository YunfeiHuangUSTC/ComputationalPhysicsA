/*
����������ҵ��11�� PB18020539 ��蹷�
�����ά����������GSAW��ָ��ֵ�������Լ�������
*/
//���ļ����е���11-1.c����11-2.c����GSAW�ĳ���
//��11-1.c�Ƕ�һ������������ߺ��¼ÿһ����λ�ã���11-2.c�Ƕ�M������������ߺ��¼λ�Ƶ�ƽ�� 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
typedef struct node {
	int x, y;
	struct node *next;
} point;
point *begin;
int x = 0, y = 0;//x,y��ʾ��ǰλ��
int Count = 0;
//16807������
int Schrage(int a, int z, int m, int q, int r) {
	int s = a * (z%q) - r * (z / q);
	if (s < 0)
		s += m;
	return s;
}
double RandGen() {
	static int I=47,a = 16807, b = 0, m = 2147483647;
	static int q, r;
	q = m / a;
	r = m % a;
	int s = Schrage(a, I, m, q, r);
	I = (s + b) % m;
	return (double)I / m;
}
//��һ������
int NextStep() {
	double judge;
	judge = RandGen();
	if (0 <= judge && judge < 0.25) {
		return 1;
	}
	else if (0.25 <= judge && judge < 0.5) {
		return 2;
	}
	else if (0.5 <= judge && judge < 0.75) {
		return 3;
	}
	else return 4;
}
//��������д������
void Memory(int x, int y) {
	point *p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->next = begin;
	begin = p;
}
//�жϸ���Ƿ�ռ�� 
int Judge2(int xn, int yn) {
	point *p = begin;
	while (((p->x != xn) || (p->y != yn)) && (p->next != NULL)) {
		p = p->next;
	}
	if (p->x == xn && p->y == yn) {
		return 1;
	}
	if (p->next == NULL) {
		return 0;
	}
	return 0;
}
//�жϡ�����ͬ��
int Judge1(int xn, int yn) {
	point *p = begin;
	while (!(Judge2(xn, yn + 1) && Judge2(xn, yn - 1) && Judge2(xn + 1, yn) && Judge2(xn - 1, yn)) && (p->next != NULL)) {
		p = p->next;
	}
	if (Judge2(xn, yn + 1) && Judge2(xn, yn - 1) && Judge2(xn + 1, yn) && Judge2(xn - 1, yn)) {
		printf("�������ֹͣ\n");
		return 1;		
	}
	if (p->next == NULL) {
		Count++;
		return 0;
	}
}
//���ߺ���
int RW() {
	int xn = x, yn = y;
	if (Judge1(xn, yn)) return 1;
w:	switch (NextStep()) {
case 1: xn = x; yn = y + 1; break;
case 2: xn = x; yn = y - 1; break;
case 3: xn = x - 1; yn = y; break;
case 4: xn = x + 1; yn = y; break;
}
	if (Judge2(xn, yn)) goto w;
	x = xn; y = yn; Memory(x, y);
	return 0;
}
int main() {
	FILE *fp1;
	if ((fp1 = fopen("WalkData.txt", "w")) == NULL) {
		printf("Failed to Open!");
		exit(0);
	}
	int N = 100;
	int i = 0;
	point *p1 = (point *)malloc(sizeof(point));
	p1->x = 0; p1->y = 0; p1->next = NULL;
	begin = p1;//��ʼλ�� 
	for (i = 0; i < N; i++) {
		if (RW()) break;
	}
	point *p = begin;//��p��������д���ļ� 
	while (p != NULL)
	{
		fprintf(fp1,"%d\t%d\n", p->x, p->y);
		p = p->next;
	}
	printf("�ܹ�����%d��\n", Count);
	fclose(fp1);
	return 0;
}
