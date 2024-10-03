#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define Max 100
 typedef struct {
 	char ten[25];
 	float tl,gt,dg;
 	int PA, sl;
 }DoVat;
 
 void readFile(DoVat **a, int *n, float *w){
 	FILE *f = fopen("CaiBalo2.txt", "r");
 	(*a) = (DoVat*)malloc(sizeof(DoVat));
 	fscanf(f , "%f", w);
 	int i =0;
 	while(!feof(f)){
 		(*a) = realloc(*a, sizeof(DoVat)* (i+1));
 		fscanf(f, "%f %f %d %[^\r\n]s",&(*a)[i].tl, &(*a)[i].gt, &(*a)[i].sl, &(*a)[i].ten);
 		(*a)[i].ten[strlen((*a)[i].ten)-1] = '\0';
 		(*a)[i].dg = (*a)[i].gt / (*a)[i].tl;
 		(*a)[i].PA = 0;
 		i++;
	 }
	 (*n) = i;
	 fclose(f);
 }
 
 void inPA(DoVat *a, int n){
 	printf("|----|---------------------|----------|----------|----------|----------|----------|\n");
 	printf("|%-2s|%-20s |%-10s|%-10s|%-10s|%-10s|%-10s|\n", "STT "," TEN DV ","TL ","GT ","DG ","SL ","PA ");
 	printf("|----|---------------------|----------|----------|----------|----------|----------|\n");
 	int i, k;
 	float tongGT =0;
 	float tongTL =0;
 	for(i=0, k=1; i < n ; i++){
 		printf("| %-2d |%-20s |%-10.1f|%-10.1f|%-10.1f|%-10d|%-10d|\n", k++, a[i].ten, a[i].tl, a[i].gt, a[i].dg, a[i].sl, a[i].PA );
 		tongGT += a[i].gt*a[i].PA;
 		tongTL += a[i].tl*a[i].PA;
	 }
	printf("|----|---------------------|----------|----------|----------|----------|----------|\n");
	printf("Phuong an duoc chon theo thu tu o ban tren la: (");
	for ( i =0; i< n-1; i++){
		printf(" %d, ", a[i].PA);
	}
	printf(")\n");
	printf("Tong gia trii duoc chon la: %9.1f\nTong trong luong lay duoc la: %-9.1f", tongGT, tongTL);
 }
 
 void swap( DoVat *a, DoVat *b){
 	DoVat tmp = *a;
 	*a = *b;
 	*b = tmp;
 }
 
 void Sort( DoVat *a, int n){
 	int i , j;
 	for ( i =0; i < n -1; i++){
 		for( j =i + 1 ; j < n; j++){
 			if(a[i].dg < a[j].dg)
 			swap(&a[i], &a[j]);
		 }
	 }
 }
 
 int min( int a, int b){
 	return a < b ? a : b;
 }
 void greedy(DoVat *a, int n, float w){
 	int i =0;
 	while((i < n) &&(w > 0)){
 		a[i].PA = min(a[i].sl, w / a[i].tl);
 		w -= a[i].tl* a[i].PA;
 		i++;
	 }
 }
 int main(){
 	int n=0;
 	float w =0;
 	DoVat *a;
 	readFile(&a,&n,&w);
 	Sort(a,n);
 	greedy(a,n, w);
 	inPA(a,n);
 	return 0;
 }
