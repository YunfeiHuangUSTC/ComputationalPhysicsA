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
#define M 3000
#define N 50 
typedef struct node {
	int x, y;
	struct node *next;
} point;
int x = 0, y = 0;//x,y��ʾ��ǰλ��
point *begin[M];
static int I=1;
//16807������
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
void Memory(int x, int y,int j) {
	point *p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->next = begin[j];
	begin[j] = p;//ÿһ�ζ�������ͷ�������µ�������˳�������ߵĹ������෴�ģ�����Ӱ���� 
}
//�жϼ�������ĸ���Ƿ�ռ�� 
int Judge2(int xn, int yn,int j) {
	point *p = begin[j];
	while (((p->x != xn) || (p->y != yn)) && (p->next != NULL)) {
		p = p->next;
	}
	if (p->x == xn && p->y == yn) {
		return 1;
	}
	if (p->next == NULL) {
		return 0;
	}
}
//�жϡ�����ͬ��
int Judge1(int xn, int yn,int  j) {
	point *p = begin[j];
	while (!(Judge2(xn, yn + 1,j) && Judge2(xn, yn - 1,j) && Judge2(xn + 1, yn,j) && Judge2(xn - 1, yn,j)) && (p->next != NULL)) {
		p = p->next;
	}
	if (Judge2(xn, yn + 1,j) && Judge2(xn, yn - 1,j) && Judge2(xn + 1, yn,j) && Judge2(xn - 1, yn,j)) {
		return 1;		
	}
	if (p->next == NULL) {
		return 0;
	}
}
//���ߺ���
int RW(int j) {
	int xn = x, yn = y;
	if (Judge1(xn, yn,j)) return 1;
w:	switch (NextStep()) {
case 1: xn = x; yn = y + 1; break;
case 2: xn = x; yn = y - 1; break;
case 3: xn = x - 1; yn = y; break;
case 4: xn = x + 1; yn = y; break;
}
	if (Judge2(xn, yn,j)) goto w;//���xn,yn��λ���е�ռ�ݣ������³��������û�е�ռ�ݣ�����һ���� 
	x = xn; y = yn; Memory(x, y,j);
	return 0;
}
int main() {
	FILE *fp1;
	if ((fp1 = fopen("Distance.txt", "w")) == NULL) {
		printf("Failed to Open!");
		exit(0);
	}
	int i = 0,j=0;
	int d[M][N];//���ڼ�¼M������ÿһ��֮����ԭ��λ��ƽ��������N�� 
	for(j=0;j<M;j++){
		x=0;y=0;
		point *p1 = (point *)malloc(sizeof(point));
		p1->x = 0; p1->y = 0; p1->next = NULL;
		begin[j] = p1;
		for (i = 0; i < N; i++) {
			if (RW(j)) {
				j--;goto next;//ϣ��ÿһ�ζ���������N������������߽�����ͬ�������¿�ʼ��ֱ��������N��Ϊֹ 
			}
		}
		point *p = begin[j];
		for(i=0;i<N;i++){
			d[j][i]=p->x*p->x+p->y*p->y;
			p=p->next; 
		}
next:		;
	}
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			fprintf(fp1,"%d\t",d[i][j]);
		}
		fprintf(fp1,"\n");
	}
	printf("done\n");
	return 0;
}

