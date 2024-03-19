#include<stdio.h>
#include<conio.h>
#define MAX 100
#define inputfile "DFS1.txt"

	int chuaXet[MAX];
	int LuuVet[MAX];

typedef struct dothi{
	int n;
	int a[MAX][MAX];
}DOTHI;
//==========================================================
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
///======================================
int XUATMATRAN(DOTHI g){
	printf("DINH : %d\n",g.n);
	printf("MATRAN\n");
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
// thuat toan DFS
void DFS(DOTHI g,int v){
 chuaXet[v]=1;
int u;
 for(u=0;u< g.n;u++){
   if(g.a[v][u] !=1 && chuaXet[u]==0)
   {
   	LuuVet[u]=v;
     DFS(g,u);
    }
 }
}
//=======================================================
//void duyettheoDFS(int s, int f,DOTHI g){
//	
//	int i;
//	
//	
//	DFS(s,g);
//	
//	if(chuaXet[f]==1){
//		
//		printf("DUONG DI TU DINH %d la :\n\t",s,f);
//		
//		i=f;
//		printf("%d",f);
//		
//	}else
//	{
//		printf("khong co duong di tu dinh % d den dinh %d \n",s,f);
//	}
//}
//=======================================================================
struct QUEUE
{
	int size;
	int a[MAX];
};

void khoitaoQUEUE(QUEUE &Q){
	Q.size=0;
}

int daygiatrivaoqueue(QUEUE &Q,	int value)
{
	if(Q.size + 1 >=100 )
		
		return 0;
		
		Q.a[Q.size]=value;
		Q.size++;
		 return 1;
}

int laygiatrirakhoiqueue(QUEUE &Q,int value)
{
	if(Q.size <= 0 )
		
			return 0;
			
	value=Q.a[0];
	for(int i=0;i<Q.size-1;i++)
	Q.a[i]=Q.a[i+1];
	
	Q.size--;
	
	return 1;		
}

int kiemtraqueuerong(QUEUE Q){
	if(Q.size<= 0)
	
		return 1;
	return 0;
}

void BFS(int v ,DOTHI g)
{
	QUEUE Q;
	khoitaoQUEUE(Q);
	daygiatrivaoqueue(Q,v);
	
	while(!kiemtraqueuerong(Q)){
		laygiatrirakhoiqueue(Q,v);
		
		chuaXet[v]=1;
		
		for(int u=0;u<g.n;u++){
			if(g.a[v][u] != 0 && chuaXet[u] == 0 ){
				daygiatrivaoqueue(Q,u);
				if(LuuVet[u]== -1)
					LuuVet[u]=v;
			}
		}
	}
}
//==================================================
//void duyettheoBFS(int s,int f, DOTHI g){
//	
//	BFS(s,g);
//	
//	if(chuaXet[f]== 1){
//		printf("Duong di tu dinh %d den dinh %d la :\n\t",s,f);
//		i=f;
//		printf("%d",f);	
//	}
//	else 
//	{
//		printf(" khong co duong di tu dinh %d den dinh %d \n",s,f);
//	}
//}
//======================================
int main(){
	DOTHI g;
		if(DOCMATRAN(inputfile,g)==1){
		printf("lay thong tin thanh cong .\n\n");
		XUATMATRAN(g);
		printf("nhap 1 dinh bat ki DFS: ");
		getch();
//		duyettheoDFS(0,2,g);
	}
	getch();
}





