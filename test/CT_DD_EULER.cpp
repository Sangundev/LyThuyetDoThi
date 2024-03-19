
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
int XUATMATRAN(DOTHI g,const char* tenfile){
	printf("DINH : %d\n",g.n);
	printf("MATRAN (%s)\n",tenfile);
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//================================================
int KiemTraDoThiVoHuong(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1; // vo huong
}
//===============================================
int KiemTraMaTranKeHopLe(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		if(g.a[i][i] != 0) // phan tu nam tren DuongCheoChinh
			return 0;
	return 1;
}
//==================================================
int batcuadinh(DOTHI g , int dinh){
	int d=0;
	for(int i=0;i<g.n;i++)
		if(g.a[dinh][i]!=0)
		d++;
		return d;
}
//====================================================
int moidinhbatchan(DOTHI g ){
	int dinh;
	for(int dinh=0;dinh<g.n;dinh++)
		if(batcuadinh(g,dinh)%2==0)
		return 1;
}
//====================================================
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
void duongdi(int i,DOTHI &tmp,STACK &s){
	for(int j=0;j<tmp.n;j++){
		if(tmp.a[i][j] != 0){
			tmp.a[i][j]=tmp.a[j][i]=0;
			duongdi(j,tmp,s);
		}
	}
	push(s,i);
}
//================================================
int xetlienthog(DOTHI g){
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
	if(SoThanhPhanLT ==1 )
	return 1;
	return 0;
}
////======================================
void euler(DOTHI g,int xp){

	DOTHI tmp= g;
	
	STACK s;
	stack(s);
	duongdi(xp,tmp,s);
	
	for(int i=s.size-1; i>0; i--) 
		printf("%d -> ", s.a[i]);
	printf("%d.", s.a[0]);

}
///================================
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
////=============================================
int main(){
	DOTHI g;
//	char inputfile[100];
	char ch;
	int xp;
	do{
//		printf("\nnhap ten do thi : ");
//		gets(inputfile);
	if(DOCMATRAN(inputfile,g)==1){
		printf("lay thong tin thanh cong .\n\n");
		XUATMATRAN(g,inputfile); 
		if(KiemTraMaTranKeHopLe(g)==1)
		{
			if(xetlienthog(g)==1){
				if(KiemTraDoThiVoHuong(g)==1){	
					printf("Do thi vo huong.\n");
					if(moidinhbatchan(g)==1){
						nhapdinhxp(g,xp);
							if(batcuadinh(g)%2==0){
								printf("chu trinh euler\n");
									euler(g,xp);
								printf("duong di euler ");
									euler(g,xp);
							}else{
								printf("chu trinh euler\n");
									euler(g,xp);	
					}
				}else{
					printf("Do thi co huong.\n");
				}
			}else printf(" k co chu trinh euler ");
		}else printf(" k hop le");
	}
		printf("\n-------------------------------------\n");
		printf("co muon tiep hay khong [Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
return 0;
}
