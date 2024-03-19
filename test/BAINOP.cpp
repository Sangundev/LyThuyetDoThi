#include <stdio.h>
#include <conio.h>
#define MAX 10
#define inputfile "1.EULER.txt"
/* Nguyen Ngoc Sang
		2011068714
			20DTHC1    */
		
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

struct NODE {
	int data;
	NODE *pNext;
};

struct stack{
	NODE *pHead;
	NODE *pTail;
};
//==============================================================
NODE *CreateNODE(int x){
	NODE *p = new NODE;
	if(p==NULL)
		return NULL;
	p->data = x;
	p->pNext = NULL;
}

void CreateStack(stack &x){
	x.pHead = NULL;
	x.pTail = NULL;
}

void Push (stack &x, int New){
	NODE *p = CreateNODE(New);
	if(x.pHead == NULL){
		x.pHead = p;
		x.pTail = p;
		return;
	}
	p->pNext = x.pHead;
	x.pHead = p;
}
//==============================================================
int DocMaTranKe(const char* TenFile,DOTHI &g){	
	FILE* f;
	f = fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	fclose(f);
	return 1;
}
//==============================================================
void XuatMaTranKe(DOTHI g,const char* TenFile)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi (%s) la:\n", TenFile);
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//==============================================================
int KiemTraMaTranKeHopLe(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		if(g.a[i][i] != 0) // phan tu nam tren DuongCheoChinh
			return 0;
	return 1;
}
//==============================================================
int KiemTraDoThiVoHuong(DOTHI g)
{
	for(int i=1;i<g.n;i++)
		for(int j=1;j<i;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1; // vo huong
}
//==============================================================
int BacVoHuong(DOTHI g, int dinh){//bac ngoai
	int dem = 0;
	for(int i = 0;i<g.n;i++){
		if(g.a[dinh][i] != 0)
			dem++;
	}
	return dem;
}
//==============================================================
int BacTrong(DOTHI g, int dinh){//bac trong
	int dem = 0;
	for(int i = 0;i<g.n;i++){
		if(g.a[i][dinh] != 0)
			dem++;
	}
	return dem;
}
//==============================================================
void DiTimCacDinhLienThong(DOTHI g, int Nhan[], int i)
{
	for(int j=0;j<g.n;j++)
	{
		if(g.a[i][j] !=0 && Nhan[j] != Nhan[i])
		{
			Nhan[j] = Nhan[i];
			DiTimCacDinhLienThong(g, Nhan, j);
		}
	}
}
//==============================================================
int XetLienThong(DOTHI g)
{
	int Nhan[MAX];
	
	for(int i=0;i<g.n;i++)
		Nhan[i] = 0;
	
	int SoThanhPhanLT = 0;
	
	for(int i=0;i<g.n;i++)
	{
		if(Nhan[i] ==0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
			DiTimCacDinhLienThong(g, Nhan, i);
		}
	}
	if(SoThanhPhanLT>1)
		return 0;
	else 
		return 1;
}
//==============================================================
int KT_ChuTrinhDuongDi_Euler_VoHuong(DOTHI g){
	int kt = 0;
	for(int i = 0;i<g.n;i++){
		if(BacVoHuong(g,i)%2 != 0)
			kt++;
	}
	return kt;
}
//==============================================================

void TimDuongDi_VoHuong(int i,DOTHI &g , stack &KQ){
	for(int j = 0; j<g.n;j++){
		if(g.a[i][j]!=0){
			g.a[i][j] = g.a[j][i]=0;
			TimDuongDi_VoHuong(j,g,KQ);
		}
	}
	Push(KQ,i);
}

void ChuTrinh_Euler_VoHuong(DOTHI g, int xp){
	stack KQ;
	CreateStack(KQ);
	DOTHI temp = g;
	TimDuongDi_VoHuong(xp,temp,KQ);
	printf("\n");
	for(NODE *p = KQ.pHead;p!=NULL;p=p->pNext){
		printf("%d->",p->data);
	}
	printf("\b\b. \n");
}
//=================================================
void DuongDi_Euler_VoHuong(DOTHI g,int xp){
	stack KQ;
	CreateStack(KQ);
	int start=0;
	
	if(BacVoHuong(g,xp)%2 !=0){
		start=xp;
	}
	DOTHI temp = g;
	TimDuongDi_VoHuong(start,temp,KQ);
	printf("\n");
	for(NODE *p = KQ.pHead;p!=NULL;p=p->pNext){
		printf("%d->",p->data);
	}
	printf("\b\b. \n");
}
//==============================================================
int KT_ChuTrinhDuongDi_Euler_CoHuong(DOTHI g){
	int kt = 0;
	for(int i = 0;i<g.n;i++){
		if(BacVoHuong(g,i) != BacTrong(g,i))
			kt++;
	}
	return kt;
}
void TimDuongDi_CoHuong(int i,DOTHI &g , stack &KQ){
	for(int j = 0; j<g.n;j++){
		if(g.a[i][j] != 0){
			g.a[i][j] = 0;
			TimDuongDi_CoHuong(j,g,KQ);
		}
	}
	Push(KQ,i);
}
//=================================
void ChuTrinh_Euler_CoHuong(DOTHI g,int xp){
	stack KQ;
	CreateStack(KQ);
	DOTHI temp = g;
	TimDuongDi_VoHuong(xp,temp,KQ);
	printf("\n");
	for(NODE *p = KQ.pHead;p!=NULL;p=p->pNext){
		printf("%d->",p->data);
	}
	printf("\b\b. \n");
}
//============================================================
void DuongDi_Euler_CoHuong(DOTHI g,int xp){
	stack KQ;
	CreateStack(KQ);
	int start =0;
	if(BacVoHuong(g,xp)%2 !=0){
		start=xp;
	}
	DOTHI temp = g;
	TimDuongDi_VoHuong(start,temp,KQ);
	printf("\n");
	for(NODE *p = KQ.pHead;p!=NULL;p=p->pNext){
		printf("%d->",p->data);
	}
	printf("\b\b. \n");
}
///========================================================
void nhapdinhxp(DOTHI g,int &dinh){
	do{
		printf("\n nhap dinh xuat phat :");
		scanf("%d",&dinh);
		if(!(0<= dinh&& dinh<g.n)) printf(" \n nhap sai ");
	}while(!(0<= dinh&& dinh<g.n));
}
//==============================================================
int main()
{
	DOTHI g;
		char ch;
		int xp;
//	char inputfile[100];
do{	
//		printf("\nnhap ten do thi : ");
//		gets(inputfile);
	if(DocMaTranKe(inputfile, g)==1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g,inputfile);	
		if(KiemTraMaTranKeHopLe(g)==1){
			printf("Do thi hop le.\n");
			if(XetLienThong(g) == 1){
				printf("\nDo thi nay lien thong\n");
				if(KiemTraDoThiVoHuong(g)==1){
					printf("\nDo thi vo huong.\n");
					for (int dinh=0;dinh<g.n;dinh++)
						printf("Dinh [%d] co bac: %d\n",dinh, BacVoHuong(g,dinh));
						nhapdinhxp(g,xp);
					if(KT_ChuTrinhDuongDi_Euler_VoHuong(g) == 0){
						printf("\nDo thi co chu trinh Euler\n");
						ChuTrinh_Euler_VoHuong(g,xp);
					}
					else if(KT_ChuTrinhDuongDi_Euler_VoHuong(g) == 2){
						printf("\nDo thi co duong di Euler\n");
						DuongDi_Euler_VoHuong(g,xp);
					}
					else{
						printf("\nDo thi ko co chu trinh va duong di Euler\n");
					}
				}
				else{
					printf("\nDo thi co huong.\n");
					printf("Bac Ngoai:\n");
					for (int dinh=0;dinh<g.n;dinh++)
						printf("Dinh [%d] co bac: %d\n", dinh, BacVoHuong(g,dinh));
					printf("\nBac Trong:\n");
					for (int dinh=0;dinh<g.n;dinh++)
						printf("Dinh [%d] co bac: %d\n", dinh, BacTrong(g,dinh));
						nhapdinhxp(g,xp);
					if(KT_ChuTrinhDuongDi_Euler_CoHuong(g) == 0){
						printf("\nDo thi co chu trinh Euler\n");
						ChuTrinh_Euler_CoHuong(g,xp);
					}
					else if(KT_ChuTrinhDuongDi_Euler_CoHuong(g) == 2){
						printf("\nDo thi co duong di Euler\n");
						DuongDi_Euler_CoHuong(g,xp);
					}
					else{
						printf("\nDo thi ko co chu trinh va duong di Euler\n");
					}
				}
			}
			else{
				printf("\nDo thi nay ko lien thong\n");
			}		
		}
		else
			printf("Do thi khong hop le.\n");
	}
		printf("\n-------------------------------------\n");
		printf("co muon tiep hay khong [Y/N]: ");
		ch=getche();
}while(ch=='Y'||ch=='y');
	return 0;
}