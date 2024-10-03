#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define Max 100;
typedef struct {
	char ten[25];
	float tl, gt, dg;
	int PA, sl;
}Dovat;

void readFile(Dovat **a, int *n, float *w){
	printf("Chon cai balo(1/2/3)\n");
	int option;
	scanf("%d", &option);
	if(option == 1){
		FILE *f = fopen("CaiBalo1.txt", "r");
		(*a) = (Dovat*)malloc(sizeof(Dovat));
		fscanf(f, "%f", w);
		int i=0;
		while(!feof(f)){
			(*a) = realloc(*a, sizeof(Dovat)*(i+1));
			fscanf(f, "%f %f %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, &(*a)[i].ten);
			(*a)[i].ten[strlen((*a)[i].ten) -1] ='\0';
			(*a)[i].dg = (*a)[i].gt/(*a)[i].tl;
			(*a)[i].sl =Max;
			(*a)[i].PA = 0;
			i++;
		}
		(*n) = i;
		fclose(f);
	}
	else {
		if(option == 2){
			FILE *f= fopen("CaiBalo2.txt", "r");
			(*a) = (Dovat*)malloc(sizeof(Dovat));
			fscanf(f, "%f", w);
			int i = 0;
			while(!feof(f)){
				(*a) = realloc(*a, sizeof(Dovat)* (i+1));
				fscanf(f, "%f %f %d %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, &(*a)[i].sl, &(*a)[i].ten );
				(*a)[i].ten[strlen((*a)[i].ten) -1] ='\0';
				(*a)[i].dg = (*a)[i].gt / (*a)[i].tl;
				(*a)[i].PA = 0;
				i++; 
			}
			(*n) = i;
			fclose(f);
		}
		else{
			FILE *f = fopen("CaiBalo3.txt", "r");
			(*a) = (Dovat*)malloc(sizeof(Dovat));
			fscanf(f,"%f", w);
			int i =0;
			while(!feof(f)){
				(*a)=realloc(*a, sizeof(Dovat)*( i+1));
				fscanf(f, "%f %f %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, (*a)[i].ten);
				(*a)[i].ten[strlen((*a)[i].ten) -1] ='\0';
				(*a)[i].sl  = 1;
				(*a)[i].dg = (*a)[i].gt / (*a)[i].tl;
				(*a)[i].PA = 0;
				i++;
			}
			(*n)= i;
			fclose(f);
		}
	}
}

void inPA(Dovat *a, int n){
	printf("|----|---------------------|-----------|--------|----------|-----------|-----------|\n");
	printf("|%-3s|%-21s|%-10s|%-7s|%-10s|%-10s|%-10s|\n"," STT","   TEN DV", "TRONG LUONG", " GIA TRI", " DON GIA","  SO LUONG ", " PHUONG AN " );
	printf("|----|---------------------|-----------|--------|----------|-----------|-----------|\n");
	int i;
	int k;
	float tongGT=0;
	float tongTL =0;
	for( i=0 ,k =1; i < n; i++){
		printf("|  %-2d| %-20s| %-10.1f| %-7.1f|%-10.1f| %-10d| %-10d|\n",k++, a[i].ten, a[i].tl, a[i].gt, a[i].dg, a[i].sl, a[i].PA );
		tongGT += a[i].gt * a[i].PA;
		tongTL += a[i].tl * a[i].PA;
	}
	printf("|----|---------------------|-----------|--------|----------|-----------|----- -----|\n");
	printf("Phuong an duoc chon theo thu tu owr bang tren: (");
	for( i= 0; i < n-1 ; i++)
		printf(" %d, ",a[i].PA);
	printf(")\n");
	printf("Tong gia tri lay duoc: %-9.1f\nTonng trong luong lay duoc: %-9.1f", tongGT, tongTL);
}

void swap(Dovat *a, Dovat *b){
	Dovat tmp = *a;
	*a =*b;
	*b = tmp;
}

void Sort(Dovat *a, int n){
	int i,j ;
	for(i =0; i < n-1 ; i++){
		for(j = i+1; j <n; j++){
			if(a[i].dg < a[j].dg)
				swap(&a[i], &a[j]);
		}
	}
}

int min( int a, int b){
	return a < b ? a : b;
}

void greedy(Dovat *a, int n, float w){
	int i =0 ;
	while(i < n && w > 0){
		a[i].PA = min(a[i].sl, (w/a[i].tl));
		w = w - a[i].PA*a[i].tl;
		i++;
	}
}
int main(){
	int n =0;
	float w =0;
	Dovat *a;
	readFile(&a,&n,&w);
	Sort(a,n);
	greedy(a,n,w);
	inPA(a, n);
	free(a);
}
