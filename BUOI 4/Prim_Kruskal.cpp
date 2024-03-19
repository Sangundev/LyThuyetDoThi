////=====================================
/// NGUYEN NGOC SANG
///2011068714
///========================
#include<stdio.h>
#include<conio.h>
#define MAX 100
#define MAX_VALUE 100
//#define inputfile "Prim_1.txt"

typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

typedef struct EDGE
{	
	int u;
	int v;
	int value;//trong so
}CANH;

int ChuaXet[MAX];
CANH T[MAX]; 
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
//======================================================================
void XuatMaTranKe(DOTHI g,const char* TenFile)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi %s la:\n",TenFile);
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
///=========================================================
int kiemtrats(DOTHI g){
	for(int i=0 ; i<g.n;i++)
		for(int j = 0 ; j<g.n;j++)
			if(g.a[i][j] !=0 && g.a[i][j] !=1 )
			return 1;
	return 0;
}
//======================================================================
int KiemTraDoThiVoHuong(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1; // vo huong
}
//====================================================================
void DiTimCacDinhLienThong(DOTHI g, int Nhan[], int i)
{
	for(int j=0;j<g.n;j++)
		if(g.a[i][j] !=0 && Nhan[j] != Nhan[i])
		{
			Nhan[j] = Nhan[i];
			DiTimCacDinhLienThong(g, Nhan, j);
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
//===========================================================
void Prim(DOTHI g,int dxdt)
{
	int nT=0;
	for(int i=0;i<g.n;i++)
		ChuaXet[i] = 0;
		ChuaXet[dxdt] = 1; //dinh xuat phat 
	while(nT<g.n-1){
		CANH CanhNhoNhat;
		int GiaTriNhoNhat=MAX_VALUE;
			for(int i=0;i<g.n;i++){
				if(ChuaXet[i] == 1)
					for(int j=0;j<g.n;j++)
						if(ChuaXet[j] == 0 && g.a[i][j] !=0 && GiaTriNhoNhat > g.a[i][j]){
							CanhNhoNhat.u=i;
							CanhNhoNhat.v=j;
							CanhNhoNhat.value = g.a[i][j];
							GiaTriNhoNhat = g.a[i][j];
						}
			}
			T[nT++]=CanhNhoNhat;
			ChuaXet[CanhNhoNhat.v] = 1;
	}
	int TongTrongSoCuaCayKhung=0;
	printf(" Cay khung nho nhat cua do thi la :\n");
	for(int i=0;i<nT;i++){
		printf("[%d,%d(%d)], ",T[i].u,T[i].v,T[i].value);
		TongTrongSoCuaCayKhung +=T[i].value;
	}
//		printf("[%d,%d(%d)], ",T[nT-1].u,T[nT-1].v,T[nT-1].value);
//		TongTrongSoCuaCayKhung +=T[nT-1].value;
		printf("\b\b\tTong =%d\n",TongTrongSoCuaCayKhung);
}
//=====================================================================
void BubbleTang(CANH E[100],int tongsocanh ){
	CANH canhtam;
	for(int i=0; i<tongsocanh-1;i++){
		for(int j=i+1;j<tongsocanh ;j++)
			if(E[i].value > E[j].value){
				canhtam = E[i];
				E[i]=E[j];
				E[j]=canhtam;
			}
	}
}
//======================================================================
void kruskal(DOTHI g)
{
	CANH listEdge[MAX];
	int tongsocanh = 0;
	int i,j;
	
	for(i=0;i<g.n-1;i++){ // bo dong cuoi xet tam giac tren 
		for(j=i+1;j<g.n;j++)
			if(g.a[i][j] > 0)
			{
				listEdge[tongsocanh].u=i;
				listEdge[tongsocanh].v=j;
				listEdge[tongsocanh].value=g.a[i][j];
				tongsocanh++;
			}
	}
	BubbleTang(listEdge, tongsocanh);
	
	int nT=0;
	CANH T[MAX];
	int nhan[MAX];
	
	for(i=0;i<g.n;i++) nhan[i]=i;
	
	int canhdangxet = 0;
	while(nT<g.n && canhdangxet < tongsocanh){
		if(nhan[listEdge[canhdangxet].u] != nhan[listEdge[canhdangxet].v])
		{
			T[nT++] = listEdge[canhdangxet];
			int giatri=nhan[listEdge[canhdangxet].v];
			for(j=0;j<g.n;j++)
				if(nhan[j] == giatri)
					nhan[j] = nhan[listEdge[canhdangxet].u];
		}
		canhdangxet++;
	}
	if(nT != g.n-1) printf("\nDo thi k lien thong nen khong cos kruskal\n");
	else
	{
		int tongtrongsocuacaykhung = 0;
//		printf("\ndothi lien thong \n");
		printf("cay khung nho nhat cua do thi la : \n");
		for(i=0;i<nT;i++)
		{
			printf("[%d,%d(%d)],",T[i].u,T[i].v,T[i].value);
			tongtrongsocuacaykhung +=T[i].value;
		}
			printf("\b\tTong =%d\n",tongtrongsocuacaykhung);
	}
}
//==========================================================
void nhapdinhxp(DOTHI g,int &dinh){
	do{
		printf("\n nhap dinh xuat phat :");
		scanf("%d",&dinh);
		if(!(0<= dinh&& dinh<g.n)) printf(" \n nhap sai ");
	}while(!(0<= dinh&& dinh<g.n));
}
//===========================================================
int main()
{
	DOTHI g;
	int k,ch;
//	char inputfile[100]="Prim_5.txt";
	char inputfile[100]="KrusKal_4.txt";
	do{
//  	printf("\n\nNhap ten file do thi: ");
//		fflush(stdin); gets(inputfile);
		if(DocMaTranKe(inputfile, g)==1) //doc file duoc
		{
			printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g,inputfile);
			
			if(KiemTraMaTranKeHopLe(g)==1)
			{ printf("Do thi hop le.\n");
				if(XetLienThong(g) == 1 )
				{ 	printf("\nDo thi lien thong. \n");
						if(kiemtrats(g)==1)
						{	printf("Do thi co trong so .\n");
							if(KiemTraDoThiVoHuong(g)==1)
							{	printf("Do thi vo huong.\n");
								
								printf("\n=========== \ Prim /============ \n");
								for(int dxdt=0;dxdt<g.n;dxdt++){
								printf("\n Prim(%d) :\n",dxdt);
								Prim(g,dxdt);
								}
								printf("\n=========== \ Kruskal /============ \n");
								for(int dxdt=0;dxdt<g.n;dxdt++){
								printf("\n Kruskal(%d) :\n",dxdt);
								kruskal(g);
								}
							}else printf("Do thi co huong.\n");
						}else printf("Do thi khong trong so .\n");
				}else printf("Do thi khong lien thong\n. ");
			}else printf(" khong hop le.\n ");
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}
