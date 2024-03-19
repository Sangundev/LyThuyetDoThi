#include<stdio.h>
#include<conio.h>
#define MAX 100
#define inputfile "DFS1.txt"

typedef struct node
{ 
	int info; //// (data cung dc)
	node* pLeft;
	node* pRight;	/// p=pointer
}Node;
typedef Node* NODEPTR;

typedef Node* STACK;
///===============================================================================
void init(Node* &pRoot)
{
	pRoot = NULL;
}
///=============================================================================
Node* createNode(int x)
{

	Node* p = new Node;
	if(p!= NULL)
	{
		p->info = x,
		p->pLeft = NULL;
		p->pRight = NULL;
	}
	return p;
}
//////=======================================================================
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
void dfs_node(int DOTHI g,int n,int n,int* chuaxet,int u ){
	int stack[MAX];
	int top = 0;
	STACK[top]=u;
	chuaxet[u]=0;
	
	int i;
	 while (top > 0){
	 	i=STACK[top--]
	 	printf("%d",i+1);
	 	
	 	for(int j = 0;j<n;j++){
	 		if(g.a[i][j] == 1 && chuaxet[j]==1)
	 		{
	 			STACK[++top] == j;
	 			chuaxet[j]=0;
			 }
		 }
	 }
}
///////////======================================
int main()
{	
	DOTHI g;
	if(DOCMATRAN(inputfile,g)==1){
		printf("lay thong tin thanh cong .\n\n");
		XUATMATRAN(g);
		printf("nhap dinh :");
		getch();
	}
	return 0;
}