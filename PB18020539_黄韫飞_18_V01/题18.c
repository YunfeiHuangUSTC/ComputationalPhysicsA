/*
PB18020539 黄韫飞 计算物理作业第18题 
*/
//题18.c用于生成DLA图形，题18-2.c用于计算维数 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 400 
#define n 6000 
int a[2 * N + 1][2 * N + 1];
int xnew=0,ynew=0;
//随机数生成器
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
//随机产生0-3四种等概率的结果 
int FourResults(){
	double a=RandGen();
	int i;
	int result; 
	for(i=0;i<4;i++){
		if((a>(double)i/4)&&(a<(double)(i+1)/4)){
			result = i;break;
		}
	}
	return result; 
}
//生成初始点
void begin(){
	int i;
	int side;
	double a;
	side=FourResults();
	//随机指定在哪一条边界 
	switch (side)
	{
	case(0):ynew = 2*N;break;
	case(1):ynew = 0; break;
	case(2):xnew = 0; break;
	case(3):xnew = 2*N; break;
	}
	a = 2*N * RandGen();
	//随机指定在边界上的位置 
	switch (side)
	{
	case(0):
	case(1):xnew=(int) a; break;
	case(2):
	case(3):ynew=(int) a; break;
	}
} 
//判断边界，返回0,1,2,3分别代表走出了上、下、左、右边界,4代表在边界内 
int Judge1(){
	if (ynew>2*N) return 0;
	if (ynew<0) return 1; 
	if (xnew<0) return 2;
	if (xnew>2*N) return 3;
	else return 4;
}
//判断是否停止行走，当点周围有点已被占据时，返回0 
int judge2(int x,int y){
	if ((a[x+1][y]==1||a[x-1][y]==1||a[x][y+1]==1||a[x][y-1]==1\
	||a[x+1][y+1]==1||a[x-1][y-1]==1||a[x-1][y+1]==1||a[x+1][y-1]==1)&&(x>0&&x<2*N)){
		return 0;
	}
	else return 1;
}
void Step(FILE *fp){
	//在边界上随机取点开始行走
	int i;
	begin();
	//每一步之前判断是否已经附着在已有的点上 
	while (judge2(xnew,ynew)){
		switch(FourResults()){
			case(0):ynew += 1;break;
			case(1):ynew -= 1; break;
			case(2):xnew -= 1; break;
			case(3):xnew += 1; break;	
		}
		//每试探一步就判断是否走出边界，周期性边界条件 
		switch(Judge1()){
			case(0): ynew-=(2*N+1);break;
			case(1): ynew+=(2*N+1);break;	
			case(2): xnew+=(2*N+1);break;
			case(3): xnew-=(2*N+1);break;
			case(4): ;
	}
	}
	a[xnew][ynew]=1;
	fprintf(fp,"%d\t%d\n",xnew,ynew); 
}
int main(){
	FILE *fp;
	if((fp=fopen("data.txt","w"))==NULL){
		printf("ERROR\n");
		exit(0);
	}
	//数组初始化 
	int i,j;
	for(i=0;i<(2*N+1);i++){
		for(j=0;j<2*N+1;j++){
			a[i][j] = 0;
		}
	}
	a[N][N] = 1;
	for(i=0;i<n;i++){
		Step(fp);
		printf("%d/%d\n",i,n);
	}
	fclose(fp);
}
