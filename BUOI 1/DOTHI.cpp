////=====================================
/// NGUYEN NGOC SANG
///2011068714
///========================
#include<stdio.h>
#include<conio.h>
#define MAX 10
#define inputfile "2.graph.txt"

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
void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
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
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1; // vo huong
}
///==========================================================
int kiemtrats(DOTHI g){
	for(int i=0 ; i<g.n;i++)
		for(int j = 0 ; j<g.n;j++)
			if(g.a[i][j] !=0 && g.a[i][j] !=1 )
			return 1;
	return 0;
}

///============================================================
int kt_batngoaivh(DOTHI g, int k ){
	int d=0;
	for (int col=0;col<g.n;col++)
	if(g.a[k][col] != 0)
	d++;
	return d;
}

//===================================================================
int kt_battrongvh(DOTHI g, int k ){
	int d=0;
	for (int row=0;row<g.n;row++)
	if(g.a[row][k] != 0)
	d++;
	return d;
}
//====================================================================
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
void XetLienThong(DOTHI g)
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
	//Hien thi nhung thanh phan lien thong
	printf ("\n So thanh phan lien thong la: %d\n",SoThanhPhanLT); 
	for (int i = 1; i <= SoThanhPhanLT; i++) 
 	{ 
		printf("Thanh phan lien thong thu %c gom cac dinh: ", 'A'+i-1); 
		for(int j = 0;j<g.n;j++)
		if(Nhan[j]=i)
		printf("%3d",j);
		
		printf("\n");
	}
}
//==============================================================
int main()
{
	DOTHI g;
	int k;
	if(DocMaTranKe(inputfile, g)==1) //doc file duoc
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
		
		if(KiemTraMaTranKeHopLe(g)==1)
			printf("Do thi hop le.\n");
		else
			printf("Do thi khong hop le.\n");
		
		if(KiemTraDoThiVoHuong(g)==1){	printf("Do thi vo huong.\n");
		for(int k=1;k<g.n;k++)
		printf(" DINH %d co bat = %d\n",k,kt_batngoaivh(g,k));
		}
		else{
			printf("Do thi co huong.\n");
			printf("\n\t\t BAT NGOAI\n");
			for(int k=1;k<g.n;k++)
			printf(" DINH %c co bat = %d\n",'A'+k-1,kt_batngoaivh(g,k));
			
			printf("\n\t\t BAT TRONG\n");
			for(int k=1;k<g.n;k++)
			printf(" DINH %c co bat = %d\n",'A'+k-1,kt_battrongvh(g,k));
		}
		if(kiemtrats(g)==1)
			printf("Do thi co trong so .\n");
		else
			printf("Do thi khong trong so .\n");
		
		XetLienThong(g);
	}
	return 0;
}
//==============================================================