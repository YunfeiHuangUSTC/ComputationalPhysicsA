/*
PB18020539 ��蹷� ����������ҵ��18�� 
*/
//��18.c��������DLAͼ�Σ���18-2.c���ڼ���ά�� 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 400 
#define n 6000 
int a[2 * N + 1][2 * N + 1];
int xnew=0,ynew=0;
//�����������
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
//�������0-3���ֵȸ��ʵĽ�� 
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
//���ɳ�ʼ��
void begin(){
	int i;
	int side;
	double a;
	side=FourResults();
	//���ָ������һ���߽� 
	switch (side)
	{
	case(0):ynew = 2*N;break;
	case(1):ynew = 0; break;
	case(2):xnew = 0; break;
	case(3):xnew = 2*N; break;
	}
	a = 2*N * RandGen();
	//���ָ���ڱ߽��ϵ�λ�� 
	switch (side)
	{
	case(0):
	case(1):xnew=(int) a; break;
	case(2):
	case(3):ynew=(int) a; break;
	}
} 
//�жϱ߽磬����0,1,2,3�ֱ�����߳����ϡ��¡����ұ߽�,4�����ڱ߽��� 
int Judge1(){
	if (ynew>2*N) return 0;
	if (ynew<0) return 1; 
	if (xnew<0) return 2;
	if (xnew>2*N) return 3;
	else return 4;
}
//�ж��Ƿ�ֹͣ���ߣ�������Χ�е��ѱ�ռ��ʱ������0 
int judge2(int x,int y){
	if ((a[x+1][y]==1||a[x-1][y]==1||a[x][y+1]==1||a[x][y-1]==1\
	||a[x+1][y+1]==1||a[x-1][y-1]==1||a[x-1][y+1]==1||a[x+1][y-1]==1)&&(x>0&&x<2*N)){
		return 0;
	}
	else return 1;
}
void Step(FILE *fp){
	//�ڱ߽������ȡ�㿪ʼ����
	int i;
	begin();
	//ÿһ��֮ǰ�ж��Ƿ��Ѿ����������еĵ��� 
	while (judge2(xnew,ynew)){
		switch(FourResults()){
			case(0):ynew += 1;break;
			case(1):ynew -= 1; break;
			case(2):xnew -= 1; break;
			case(3):xnew += 1; break;	
		}
		//ÿ��̽һ�����ж��Ƿ��߳��߽磬�����Ա߽����� 
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
	//�����ʼ�� 
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
