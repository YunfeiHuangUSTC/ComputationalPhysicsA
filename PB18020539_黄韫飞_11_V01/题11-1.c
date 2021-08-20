/*
计算物理作业第11题 PB18020539 黄韫飞
计算二维正方格子中GSAW的指数值，并定性加以讨论
*/
//此文件夹中的题11-1.c和题11-2.c都是GSAW的程序
//题11-1.c是对一个粒子随机行走后记录每一步的位置；题11-2.c是对M个粒子随机行走后记录位移的平方 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
typedef struct node {
	int x, y;
	struct node *next;
} point;
point *begin;
int x = 0, y = 0;//x,y表示当前位置
int Count = 0;
//16807产生器
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
//下一步行走
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
//将点坐标写入链表
void Memory(int x, int y) {
	point *p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->next = begin;
	begin = p;
}
//判断格点是否被占据 
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
//判断“死胡同”
int Judge1(int xn, int yn) {
	point *p = begin;
	while (!(Judge2(xn, yn + 1) && Judge2(xn, yn - 1) && Judge2(xn + 1, yn) && Judge2(xn - 1, yn)) && (p->next != NULL)) {
		p = p->next;
	}
	if (Judge2(xn, yn + 1) && Judge2(xn, yn - 1) && Judge2(xn + 1, yn) && Judge2(xn - 1, yn)) {
		printf("随机行走停止\n");
		return 1;		
	}
	if (p->next == NULL) {
		Count++;
		return 0;
	}
}
//行走函数
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
	begin = p1;//初始位置 
	for (i = 0; i < N; i++) {
		if (RW()) break;
	}
	point *p = begin;//用p遍历链表，写入文件 
	while (p != NULL)
	{
		fprintf(fp1,"%d\t%d\n", p->x, p->y);
		p = p->next;
	}
	printf("总共走了%d步\n", Count);
	fclose(fp1);
	return 0;
}
