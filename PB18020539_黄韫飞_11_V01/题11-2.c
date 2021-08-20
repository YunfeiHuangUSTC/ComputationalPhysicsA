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
#define M 3000
#define N 50 
typedef struct node {
	int x, y;
	struct node *next;
} point;
int x = 0, y = 0;//x,y表示当前位置
point *begin[M];
static int I=1;
//16807产生器
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
void Memory(int x, int y,int j) {
	point *p = (point *)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	p->next = begin[j];
	begin[j] = p;//每一次都在链表头部插入新点后，链表的顺序与行走的过程是相反的，但不影响结果 
}
//判断即将进入的格点是否被占据 
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
//判断“死胡同”
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
//行走函数
int RW(int j) {
	int xn = x, yn = y;
	if (Judge1(xn, yn,j)) return 1;
w:	switch (NextStep()) {
case 1: xn = x; yn = y + 1; break;
case 2: xn = x; yn = y - 1; break;
case 3: xn = x - 1; yn = y; break;
case 4: xn = x + 1; yn = y; break;
}
	if (Judge2(xn, yn,j)) goto w;//如果xn,yn的位置有点占据，则重新抽样，如果没有点占据，则走一步。 
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
	int d[M][N];//用于记录M个粒子每一步之后离原点位移平方，共走N步 
	for(j=0;j<M;j++){
		x=0;y=0;
		point *p1 = (point *)malloc(sizeof(point));
		p1->x = 0; p1->y = 0; p1->next = NULL;
		begin[j] = p1;
		for (i = 0; i < N; i++) {
			if (RW(j)) {
				j--;goto next;//希望每一次都能至少走N步，所以如果走进死胡同，则重新开始，直到可以走N步为止 
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

