#include<stdio.h>
#include<conio.h>
#define MAX 100

typedef struct dothi{
	int n;
	int a[MAX][MAX];
}DOTHI;
typedef struct STACK{
	int a[MAX];
	int size;
};
///========================================================
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
//===============================================================
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
	if(SoThanhPhanLT ==1 )	return 1;
	return 0;
}
//=========================================
void duongdi_vohuong(int i,DOTHI &tmp,STACK &s){ //vo huong
	for(int j=0;j<tmp.n;j++){
		if(tmp.a[i][j] != 0){
			tmp.a[i][j]=tmp.a[j][i]=0; // xoa canh i-j
			duongdi_vohuong(j,tmp,s);
		}
	}
	push(s,i);
}
//======================================================
void duongdi_cohuong(int i,DOTHI &tmp,STACK &s){
	for(int j=0;j<tmp.n;j++){
		if(tmp.a[i][j] != 0){
			tmp.a[i][j]=0; // xoa cung i->j
			duongdi_cohuong(j,tmp,s);
		}
	}
	push(s,i);
}
////======================================
void euler(DOTHI g,int xp){

	DOTHI tmp= g;
	
	STACK s;
	stack(s);
	
	if(KiemTraDoThiVoHuong(g) == 1 ) duongdi_vohuong(xp,tmp,s);
	else duongdi_cohuong(xp,tmp,s);
	
	//ket qua 
	for(int i=s.size-1; i>0; i--) 
		printf("%d -> ", s.a[i]);
	printf("%d.\n", s.a[0]);

}
//=============================================
int batcuadinh(DOTHI g , int dinh){
	int d=0;
	for(int i=0;i<g.n;i++)
		if(g.a[dinh][i]!=0)
		d++;
		return d;
}
//====================================================
int BacTrong(DOTHI g, int dinh){//bac trong
	int dem = 0;
	for(int i = 0;i<g.n;i++){
		if(g.a[i][dinh] != 0)
			dem++;
	}
	return dem;
}
//================================================
void SLDINHCOBACCAHNLE(DOTHI g, int &chan , int & le){//vo huong
	chan=le=0;
	for(int i=0; i<g.n;i++){
	if(batcuadinh(g,i)%2==0)   chan++;
	else le++;
	}
}
//=========================================
void xet_euler(DOTHI g, int &d_bangnhau , int & xp){//co huong
	d_bangnhau=0;
	for(int i=0; i<g.n;i++){
		if(batcuadinh(g,i) == BacTrong(g,i))   d_bangnhau++;
		else if(batcuadinh(g,i) - BacTrong(g,i)==1) 
		xp=i;
	}
}
//==================================================================
void nhapdinhxp(DOTHI g,int &dinh){
	do{
		printf("\n nhap dinh xuat phat :");
		scanf("%d",&dinh);
		if(!(0<= dinh&& dinh<g.n)) printf(" \n nhap sai ");
	}while(!(0<= dinh&& dinh<g.n));
}
////=============================================
int main(){
	DOTHI g;
	char inputfile[100];
	int ch;
	do{
		printf("\nnhap ten do thi : ");
		gets(inputfile);
		
	if(DOCMATRAN(inputfile,g)==1)
	{	printf("lay thong tin thanh cong .\n\n");
		XUATMATRAN(g,inputfile); 
		
		if(KiemTraMaTranKeHopLe(g)==1)
		{ printf("\nDo thi hop le .\n");
		
			if(xetlienthog(g)==1)
			{ printf("\nDo thi lien thong .\n");
			
				if(KiemTraDoThiVoHuong(g)==1){	
					printf("Do thi vo huong.\n");
					int chan,le;
					SLDINHCOBACCAHNLE( g, chan , le);
					if(le==0)//if(chan==g.n)
					{
						printf("\n CHU TRINH EULER : \n");
//						nhapdinhxp(g,xp);
						for(int xp = 0;xp<g.n;xp++)
							euler(g,xp);
					}else if(le==2){
						printf("\n DUONG DI EULER :\n");
						for(int xp = 0;xp<g.n;xp++)
						if(batcuadinh(g,xp) %2 !=0)
							euler( g,xp);
					} else printf(" khong co euler ");
				}else{
					printf("Do thi co huong.\n");
					int d_bangnhau , xp;
					xet_euler( g,d_bangnhau , xp);
					if(d_bangnhau==g.n){
						printf("\n CHU TRINH EULER \n");
//						nhapdinhxp(g,xp);
						for(int xp = 0;xp<g.n;xp++)
							euler(g,xp);
					}else if(d_bangnhau==g.n-2){
							printf("\n Duong di Euler :\n");
							for(int xp = 0;xp<g.n;xp++)
							euler( g,xp);
						}
					else printf(" khong co euler ");	
				}
			}else printf(" Do thi khong lien thong  ");
		}else printf(" k hop le");
	}
		printf("\n-------------------------------------\n");
		printf("co muon tiep hay khong [Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
return 0;
}
