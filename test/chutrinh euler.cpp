
// Chi ap dung voi Do thi vo huong

#include<stdio.h>
#include<conio.h>
#define MAX 20
#define MAXSTACK 100	//max SATCK

#define inputfile "1.EULER.txt"

typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

struct STACK
{	int array[MAXSTACK];
	int size;
};
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
void XuatMaTranKe(DOTHI g){	
	printf("DINH : %d\n",g.n);
	printf("MATRAN\n");
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//==============================================================
void KhoiTaoStack(STACK &stack) // InitStack
{	stack.size =0;
}
//==============================================================
void DayGiaTriVaoStack(STACK &stack, int value) //Push
{	if(stack.size+1 >= MAXSTACK) return; // IsFull
	stack.array[stack.size] = value;
	stack.size++;
}
//==============================================================
void TimDuongDi(int i, DOTHI &g, STACK &stack)
{
	for(int j=0;j<g.n;j++)
	{	if(g.a[i][j] !=0)
		{	g.a[i][j]=g.a[j][i] =0; // xoa canh
			TimDuongDi(j, g, stack);
		}
	}
	DayGiaTriVaoStack(stack,i); //Push
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
int KiemTraChuTrinhEuler(DOTHI g)
{
	//x la gia tri dinh bat dau xet chu trinh
	// Euler, dieu kien x là dinh phai có bac > 0 
 	int x = 5 ;
	// CODE: tim dinh x có bac > 0 dau tien  
 	for(x;x<g.n;x++)	
	{
		for(int i = 0 ;i<g.n;i++)
		{
			if(g.a[i][x] != 0)
			break;
		}
			break;
	}
	DOTHI temp = g;//thong qua do thi trung gian
	STACK stack;
	KhoiTaoStack(stack);
	TimDuongDi(x,temp,stack);
	int SoThanhPhanLT = 0, Nhan[MAX];
	for(int i=0;i<g.n;i++)
	{
		if(Nhan[i] ==0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
			DiTimCacDinhLienThong(g, Nhan, i);
		}
	}
	if(SoThanhPhanLT>1) return 0;
	// CODE kiem tra co ton tai cung hay duong di khong?
	int d=0;
	for(int j=0;j<temp.n;j++)
	{
		for(int i=0;i<temp.n;i++)
		{
			if(temp.a[j][i] != 0 )
				d++;
		}
	}
	if(d>0)	return 0;
	for(int i=stack.size-1;i>0;i--)
	{
		if(g.a[stack.array[i]][stack.array[i-1]]==0)
			return 0;
	}
 	// CODE dinh xuat phat == dinh ket thuc ?
 
	if(stack.array[0] != x)
		return 0;
	printf("\n Chu Trinh Euler Xuat Phat Tu Dinh %d:\n", x); 
 	
	// CODE xuat ket qua
	for(int i=stack.size-1; i > 0 ; i--)
		printf("%d -> ", stack.array[i]);
	printf("%d.\n", stack.array[0]);
	return 1;
}
//==============================================================
int KiemTraDuongDiEuler(DOTHI g)
{
	//x la gia tri dinh bat dau xet chu trinh
	// Euler, dieu kien x là dinh phai có bac > 0 
 	int x = 5 ;
	// CODE: tim dinh x có bac > 0 dau tien  
 	for(x;x<g.n;x++)	
	{
		int d=0;
		for(int i = 0 ;i<g.n;i++)
		{
			if(g.a[i][x] != 0)
			 	d++;
		}
		if(d>0&&d%2==0)
			continue;
		break;
	}
	DOTHI temp = g;//thong qua do thi trung gian
	STACK stack;
	KhoiTaoStack(stack);
	TimDuongDi(x,temp,stack);
	int SoThanhPhanLT = 0, Nhan[MAX];
	for(int i=0;i<g.n;i++)
	{
		if(Nhan[i] ==0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
			DiTimCacDinhLienThong(g, Nhan, i);
		}
	}
	if(SoThanhPhanLT>1) return 0;
	// CODE kiem tra co ton tai cung hay duong di khong?
	int d=0;
	for(int j=0;j<temp.n;j++)
	{
		for(int i=0;i<temp.n;i++)
		{
			if(temp.a[j][i] != 0 )
				d++;
		}
	}
	if(d>0)	return 0;
	for(int i=stack.size-1;i>0;i--)
	{
		if(g.a[stack.array[i]][stack.array[i-1]]==0)
			return 0;
	}
	if(stack.array[0] == x)
		return 0;
	printf("\nDuong Di Euler Xuat Phat Tu Dinh %d:\n", x); 
 	
	// CODE xuat ket qua
	for(int i=stack.size-1; i > 0 ; i--)
		printf("%d -> ", stack.array[i]);
	printf("%d.\n", stack.array[0]);
	return 1;
}
//==================================================
int batcuadinh(DOTHI g){
	 int dinh;
	int d=0;
	for(int i=0;i<g.n;i++)
		if(g.a[dinh][i]!=0)
		d++;
		return d;
}
//===============================================================
void nhapdinhxp(DOTHI g,int &dinh){
	do{
		printf("\n nhap dinh xuat phat :");
		scanf("%d",&dinh);
		if(!(0<= dinh&& dinh<g.n)) printf(" \n nhap sai ");
	}while(!(0<= dinh&& dinh<g.n));
}
//=============================================
void nhapdinhxple(DOTHI g,int &dinh){
	int tmp;
	do{
		printf("\n nhap dinh xuat phat :");
		scanf("%d",&dinh);
		 tmp=batcuadinh(g,dinh)%2;
		if(tmp== 0) printf(" \n nhap sai ");
	}while(tmp== 0);
}
//==============================================================
int main()
{
	DOTHI g;
	int dinh ;
	if(DocMaTranKe(inputfile, g)==1) 
	{
		printf("\n Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
		if( ! KiemTraChuTrinhEuler( g ))
			{
					printf("\n Khong co chu trinh Euler.\n");
					
					nhapdinhxp(g,dinh);
					if(! KiemTraDuongDiEuler( g ))
						printf("\n Khong co chu trinh Euler.\n");
			}
		if(batcuadinh(g)%2!=0){
			printf(" \nton tai suong di euler.\n ");
			KiemTraDuongDiEuler(g);
		}else{
			printf(" khong ton tai suong di euler");
		}
	}
		
	return 0;
}

