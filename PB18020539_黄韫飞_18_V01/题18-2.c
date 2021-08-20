#include<stdio.h>
#include<math.h>
#define n 6000
#define N 400
//题18.c用于生成DLA图形，题18-2.c用于计算维数 
int SandBox(){
	FILE *fp1;
	if((fp1=fopen("sandbox.txt","w+"))==NULL){
		printf("ERROR\n");
		return 0;
	}
	FILE *fp;
	double rmin=1,rmax=110,rstep=1,r;
	int x,y,i;
	for(r=rmin;r<rmax;r+=rstep){
		if((fp=fopen("data.txt","r"))==NULL){
			printf("ERROR\n");
			return 0;
		}
		int count=0;
		//如果点在半径为r的圆内，就count++ 
		for(i=0;i<n;i++){
			fscanf(fp,"%d\t%d",&x,&y);
			if(sqrt(pow(x-400,2)+pow(y-400,2))<=r){
				count++;
			}
		}
		fprintf(fp1,"%lf\t%d\n",r,count);
		fclose(fp);
	}
	fclose(fp1);
}
//判断以(a,b)为左下角，e为边长的小正方形内有无点，如果有则返回1 
int Judge(double a,double b,double e,FILE *fp){
	int i;
	int x,y;
	for(i=0;i<n;i++){
		fscanf(fp,"%d\t%d",&x,&y);
		if((x>=a)&&(x<(a+e))&&(y>=b)&&(y<(b+e))){
			return 1;
		}
	}
	return 0;
} 
int BoxCount(){
	int i,j,k,count;
	FILE *fp2;
	if((fp2=fopen("boxcount.txt","w+"))==NULL){
		printf("ERROR\n");
		return 0;
	}
	FILE *fp;
	double xmin=350,xmax=450;
	double xx=xmax-xmin;
	double e[7]={100,50,25,10,5,2,1};//e代表不同的网格尺寸 
	double num[7];
	for(i=0;i<7;i++){
		num[i]=xx/e[i];
	}
	for(i=0;i<7;i++){
		count=0;
		for(j=0;j<num[i];j++){
			for(k=0;k<num[i];k++){
				if((fp=fopen("data.txt","r"))==NULL){
					printf("ERROR2\n");
					return 0;
				}
				//遍历[xmin,xmax]之内所有的网格，如果有像素点则count++ 
				if(Judge(xmin+j*e[i],xmin+k*e[i],e[i],fp)){
					count++;
				}
				fclose(fp);
			}
		}
		printf("%lf\t%d\n",e[i],count);
		fprintf(fp2,"%lf\t%d\n",e[i],count);		
	}
}
int main(){
	SandBox();
	BoxCount();
} 
