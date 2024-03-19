#include<stdio.h>
#include<conio.h>
#define MAX 100
//#define inputfile "BFS-1.txt"
//chi ap dung hop le vo huong 

typedef struct dothi{
	int n;
	int a[MAX][MAX];
}DOTHI;

int chuaXet[MAX];
int LuuVet[MAX];
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
int XUATMATRAN(DOTHI g,const char* tenfile){
	printf("DINH : %d\n",g.n);
	printf("MATRAN %s\n\n",tenfile);
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
// thuat toan DFS
void DFS(int v,DOTHI g){
	chuaXet[v]=1;
 	for(int u=0;u< g.n;u++)
	{
   		if(g.a[v][u] !=0 && chuaXet[u]==0)
   		{
		   	LuuVet[u]=v;
		    DFS(u,g);
    	}
 	}
}
//=====================================
void ketqua_dequy(int s, int f){
	if(f != s ) ketqua_dequy(s,LuuVet[f]);
	printf("%d -> ",f);
}
//=======================================================
void duyettheoDFS(int s, int f,DOTHI g){
	
	int i;
	for( i=0 ; i<g.n;i++)
	{
		LuuVet[i]=-1;
		chuaXet[i]=0;
	}
	DFS(s,g);
	
	if(chuaXet[f]==1){
		printf("DUONG DI TU DINH %d -> %d la :\n\t",s,f);                                     
		//code: xuat phat duong di f<-s dua vao luuvet
		
//		while(f!=s)
//		{
//			printf(" < - %d",LuuVet[f]);
//			f = LuuVet[f];
//		}
			ketqua_dequy(s,f);
			printf("\b\b\b\b.  ");
	}else
		printf("khong co duong di tu dinh % d den dinh %d \n",s,f);
}
//=======================================================================
struct QUEUE
{	int a[MAX];
	int size;
};
void KhoiTaoQueue(QUEUE &Q) // InitQueue
{	Q.size = 0;
}
//==============================================================
int KiemTraQueueRong(QUEUE &Q) // IsEmpty
{	return (Q.size <= 0);
}
//==============================================================
int DayGiaTriVaoQueue(QUEUE &Q, int value) //Insert
{	if(Q.size+1 >= MAX) return 0; // IsFull
	Q.a[Q.size] = value;
	Q.size++;
	return 1;
}
//==============================================================
int LayGiaTriRaKhoiQueue(QUEUE &Q, int& value) //Remove
{	if(Q.size <= 0) return 0; // IsEmpty
	value = Q.a[0]; // lay phan tu dau Queue
	for(int i=0; i<Q.size-1; i++) // Dun day Queue xuong
		Q.a[i] = Q.a[i+1];
	Q.size--;
	return 1;
}
//==============================================================
void BFS(int v, DOTHI g)
{
	QUEUE Q;
	KhoiTaoQueue(Q);
	DayGiaTriVaoQueue(Q,v);
	while( ! KiemTraQueueRong(Q))
	{
		LayGiaTriRaKhoiQueue(Q,v);
		chuaXet[v] = 1; // bat dau xet dinh v
		for(int u=0; u<g.n; u++)
		{
			if(g.a[v][u] !=0 && chuaXet[u] ==0 && LuuVet[u] == -1) // dinh v,u ke nhau va u chua xet 
			{	
				DayGiaTriVaoQueue(Q,u); // day dinh u vao Queue
				LuuVet[u] = v;  
			}
		}
	}
}
//==============================================================
void DuyetTheoBFS(int S, int F, DOTHI g)
{
	for(int i=0; i<g.n; i++)
	{
		LuuVet[i] = -1;
		chuaXet[i] = 0;
	}
	BFS(S, g);
	if(chuaXet[F] == 1) // co duong di tu S -> F
	{	
		printf("\n BFS: Duong di tu dinh %d -> %d la:\n\t", S, F);
		ketqua_dequy(S, F);
		printf("\b\b\b\b.   \n");
	}
	else printf("\n Khong co duong di tu dinh %d -> %d.\n", S, F);
}
//==============================================================
int main()
{
	DOTHI g;
		
	char inputfile[100]="BFS-1.txt";
	char ch;
	int S,F;
	do
	{
//		printf("\n\nNhap ten file do thi: ");
//		fflush(stdin); gets(inputfile);
		if(DOCMATRAN(inputfile, g)==1) 
		{
			printf("\n Da lay thong tin do thi tu file thanh cong.\n\n");
			XUATMATRAN(g,inputfile);
		
			printf("\n Nhap Dinh bat dau: "); scanf("%d", &S);
			printf("\n Nhap Dinh ket thuc: "); scanf("%d", &F);
			
			duyettheoDFS(S,F,g);
			
			DuyetTheoBFS(S,F,g);
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}


