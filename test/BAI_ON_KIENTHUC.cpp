#include<stdio.h>
#include<conio.h>
#define MAX 100
#define inputfile "1.EULER.txt"

typedef struct dothi{
	int n;
	int a[MAX][MAX];
}DOTHI;

///====================================
int DOCMATRAN(const char* tenfile,DOTHI &g){
	FILE* f;
	f=fopen(tenfile,"rt");
	if(f==NULL){
		printf("khong ton tai file or (khong mo duoc file)\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	fclose(f);
	return 1;		
}
//=========================================
int XUATMATRAN(DOTHI g){
	printf("DINH : %d\n",g.n);
	printf("MATRAN\n");
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//=========================================
typedef struct STACK{
	int a[MAX];
	int size;
};
///===========================
void stack(STACK &s){
	s.size=0;
}
///================================================
void push(STACK &s,int value){
	if(s.size+1 >= MAX)
		return ;
	s.a[s.size]=value;
	s.size++;
}
///===================================
void duongdi(int i,DOTHI &g,STACK &s){
	for(int j=0;j<g.n;j++){
		if(g.a[i][j] != 0){
			g.a[i][j]=g.a[j][i]=0;
			duongdi(j,g,s);
		}
	}
	push(s,i);
}
//================================================
int KtraDoThiEuler(DOTHI g){
	int S = 0; 
		for (int i=0; i<g.n;i++){   
          	for(int j=0;j<g.n;j++)
                      if(g.a[i][j] != 0)     
					    S = S + 1;
          if( S%2==1 )
                      return 0;
      }
      return 1;
}
////======================================
//int kiemtrachutrinheuler(DOTHI g){
//	int i,j;
//	int x=0;
//}
////=============================================
int main(){
	DOTHI g;
	if(DOCMATRAN(inputfile,g)==1){
		printf("lay thong tin thanh cong .\n\n");
		XUATMATRAN(g);
		printf("nhap dinh :");
		getch();
	}
}
