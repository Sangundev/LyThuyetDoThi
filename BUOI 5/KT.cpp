////=====================================
/// NGUYEN NGOC SANG
///2011068714
///========================
//ap dung hop le, co trong so duong 
#include<stdio.h>
#include<conio.h>
#define MAX 100
#define VOCUC 100

int ChuaXet[MAX];
int LuuVet[MAX];
int DoDaiDuongDiToi[MAX];
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

//==============================================================
int DocMaTranKe(const char* TenFile,DOTHI &g)
{	FILE* f;
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
	printf("Ma tran ke cua do thi %s la:\n",TenFile);
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//======================================================
int KiemTraMaTranKeHopLe(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		if(g.a[i][i] != 0) // phan tu nam tren DuongCheoChinh
			return 0;
	return 1;
}
//===================================================
int kiemtrats(DOTHI g){
	for(int i=0 ; i<g.n;i++)
		for(int j = 0 ; j<g.n;j++)
			if(g.a[i][j] !=0 && g.a[i][j] !=1 )
			return 1;
	return 0;
}
//==========================================================
int kiemtratsduong(DOTHI g){
	int flag =0;//k ts
	for(int i=0 ; i<g.n;i++)
		for(int j = 0 ; j<g.n;j++)
		{
			if(g.a[i][j] < 0 )   return 0;//ts am
			if(g.a[i][j] >1 )     flag = 1;
		}
	return flag;
}
//==============================================================
int timduongdinhonhat(DOTHI g)
{
	int li=-1;
	float p= VOCUC;
	for(int i=0 ;i<g.n;i++)
	{
		if(ChuaXet[i] == 0 && DoDaiDuongDiToi[i]<p)
		{
			p=DoDaiDuongDiToi[i];
			li=i;
		}
	} return li;
}

void capnhatduongdi(int u, DOTHI g)
{
	ChuaXet[u] = 1;
	for(int v=0;v<g.n;v++)
	{
		if(ChuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC )
			if(DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v])
			{
				DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
				LuuVet[v] = u;
			}
	}
}
//=========================================================
void KetQua_DeQui(int S, int F)
{
	if(F != S) KetQua_DeQui(S, LuuVet[F]);
	printf("%d -> ", F);
}
//=============================================================
int DIJKSTRA (int S, int F, DOTHI g)
{
	//khoi tao 
	int i;
	for(i=0;i<g.n; i++)
	{
		ChuaXet[i] = 0;
		DoDaiDuongDiToi[i] = VOCUC;
		LuuVet[i] = -1;
	}
	//thuat toan 
	
	DoDaiDuongDiToi[S] = 0;
	while(ChuaXet[F] == 0)
	{
		int u = timduongdinhonhat(g);
		if(u == -1)  break;
		capnhatduongdi(u,g);
	}
	if(ChuaXet[F] == 1){
		printf(" Duong di ngan nhat tu dinh %d den dinh %d la : \n\t ",S,F);
//		i=F;
//		printf("%d",F);
//		while(LuuVet[i] != S)
//		{
//			printf("<-%d",LuuVet[i]);
//			i=LuuVet[i];
//		}
//		printf("<-%d",LuuVet[i]);

		KetQua_DeQui(S,F);
		printf("\b\b\b\b.");
		
		printf("\tsum = %d\n",DoDaiDuongDiToi[F]);
	}else{
		printf(" khong co duong di tu dinh %d den dinh %d \n",S,F);
	}
}

//============================================================================
void FLOYD(int S,int F,DOTHI g)
{
	//khoi tao 
	int i,j;
	for(i=0;i<g.n;i++)
		for(j=0;j<g.n;j++)
			if(g.a[i][j] > 0 )
			{
				Sau_Nut[i][j] = j;
				L[i][j] = g.a[i][j];
			}
			else if(i!=j)
			{
				Sau_Nut[i][j] = -1;
				L[i][j] = VOCUC;
			}
	//thi hanh flo
	for(int k=0;k<g.n;k++){
		for(int i=0;i<g.n;i++){
			for(j=0;j<g.n;j++){
				if(i != j && i!=k && j!= k )
				
				if(L[i][k] != VOCUC && L[k][j] != VOCUC)
					
					if(L[i][j] > L[i][k] + L[k][j]){
					L[i][j] = L[i][k]+L[k][j];
					Sau_Nut[i][j]=Sau_Nut[i][k];
				}
			}
		}
	}

	if(Sau_Nut[S][F] == -1)
	{
		printf("khong co duong di tu dinh %d den dinh %d\n :",S,F);
	}
	else{
		printf(" duong di ngan nhat tu dinh %d den dinh %d la :\n",S,F);
		printf("\t%d",S);
		int u=S;
		while(Sau_Nut[u][F] != F)
		{
			u=Sau_Nut[u][F];
			printf(" -> %d",u);
			
		}
		printf(" -> %d.",F);
		printf("\tsum = %d",L[S][F]);
	}
}
//===========================================================
int main()
{
	DOTHI g;
	int k,ch;
	int S,F;
	char inputfile[100]="Dij4.txt";
do{
//		printf("\n\nNhap ten file do thi: ");
//		fflush(stdin); gets(inputfile);
		if(DocMaTranKe(inputfile, g)==1) 
		{
			printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g,inputfile);
			if(KiemTraMaTranKeHopLe(g)==1)
			{ printf("Do thi hop le.\n");
				if(kiemtratsduong(g)==1)
				{	printf("Do thi co trong so duong .\n");
		//			printf("\n Nhap Dinh bat dau: "); scanf("%d", &S);
		//			printf("\n Nhap Dinh ket thuc: "); scanf("%d", &F);
					
					printf("\n========\ DIJKSTRA /========\n");
					DIJKSTRA(1,4,g);
					
	 				printf("\n========\ FLOYD /========\n");
					FLOYD(1,4,g);
				
				}else printf("Do thi co trong so am hoac k trong so .\n");
			}else printf(" khong hop le.\n ");
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}
