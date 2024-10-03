#include "stdio.h"
#include "conio.h"
#include "String.h"
#include "malloc.h"

typedef struct{
	char ten[25];
	float DG, TL, GT;
	int soDV, SL;
}DoVat;

void readFile( DoVat **m, int *n, float *w){
	FILE *f = fopen("CaiBalo2.txt","r");
	(*m) = (DoVat*)malloc(sizeof(DoVat));
	fscanf(f, "%f", w);
	int i= 0;
	while(!feof(f)){
		(*m) = realloc(*m,sizeof(DoVat)*(i+1));
		fscanf(f, " %f %f %d %[^\r\n]s", &(*m)[i].TL, &(*m)[i].GT, &(*m)[i].SL, &(*m)[i].ten);
		(*m)[i].ten[strlen((*m)[i].ten)-1]='\0';
		(*m)[i].DG = (*m)[i].GT / (*m)[i].TL;
		(*m)[i].soDV =0;
		i++;
	}
	*n= i;
	fclose(f);
}

void Swap(DoVat *a, DoVat *b){
	DoVat tam =*a;
	*a = *b;
	*b = tam;
}

void Sort(DoVat *m, int n){
	int i, j;
	for(i=0; i< n-1; i++)
		for( j= i+1; j<n; j++)
			if(m[i].DG < m[j].DG)
				Swap(&m[i],&m[j]);
}
void inDS(DoVat *m, int n){
	printf("|----|---------------------|-------------|--------|-----------|------------|-----------|\n");
	printf("|%-3s|%-21s|%-10s|%-7s|%-10s | %-10s | %-10s|\n"," STT","  Ten do vat","  Trong luong"," Gia tri"," Don gia ","So luong ", "Phuong an");
	printf("|----|---------------------|-------------|--------|-----------|------------|-----------|\n");
	int i=0;
	float tong =0;
	int TL=0;
	for(i; i< n; i++){
		printf("| %-3d| %-20s|   %-8.2f  |   %-5.2f|  %-8.2f |   %-8d |   %-8d|\n", i+1, m[i].ten, m[i].TL, m[i].GT, m[i].DG, m[i].SL, m[i].soDV);
		tong += m[i].GT*m[i].soDV;
		TL += m[i].TL*m[i].soDV;
	}
	printf("|----|---------------------|-------------|--------|-----------|------------|-----------|\n");
	printf("\nPhuown an duoc chon: (");
	for( i=0; i<n-1; i++)
		printf(" %d,", m[i].soDV);
	printf(")\n");
	printf("\nTong gia tri lay duoc: %-9.2f\nTong trong luong: %d\n",tong, TL);
}

int min(int a, int b){
	if( a < b)
		return a;
	else
		return b;
}

void nutGoc(float w, float *TLCL, float *CT, float *GiaLNTT, float *TGT, float DGLN )
{
	*TGT =0.0;
	*TLCL = w;
	*CT = *TLCL * DGLN;
	*GiaLNTT = 0.0;
}

void capNhat(float TGT, float *GiaLNTT, int x[], DoVat *m, int n)
{
	int i;
	if ( *GiaLNTT < TGT)
		*GiaLNTT = TGT;
		for( i=0; i <n ; i++)
			m[i].soDV = x[i];
}

void nhanhCan(int i, float *TGT, float *CT, float *TLCL,float *GiaLNTT, int x[],DoVat *m, int n)
{
	int j;
	int soDVmax = min(*TLCL/ m[i].TL, m[i].SL);
	for( j = soDVmax; j>=0; j--){
		*TGT += j* m[i].GT;
		*TLCL-= j* m[i].TL;
		*CT = *TGT + *TLCL * m[i+1].DG;
		if ( *CT > *GiaLNTT){
			x[i] = j;
			if ( i== n-1 || *TLCL ==0.0){
				capNhat(*TGT,GiaLNTT,x,m,n);
			}else{
				nhanhCan(i+1,TGT,CT,TLCL,GiaLNTT,x,m,n);
			}
		}
	x[i] =0;
	*TGT-= j*m[i].GT;
	*TLCL+= j*m[i].TL;
	}
	

}
int main(){
	int n;
	float w, CT, TGT,TLCL, GiaLNTT;
	DoVat *m;
	readFile(&m, &n, &w);
	int x[n];
	Sort(m,n);
	nutGoc(w,&TLCL,&CT,&GiaLNTT,&TGT,m[0].DG);
	nhanhCan(0,&TGT,&CT,&TLCL,&GiaLNTT,x,m,n);
	inDS(m,n);
    free(m);
	
}
