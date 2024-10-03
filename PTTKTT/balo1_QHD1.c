#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 typedef struct{
 	char name[25];
 	int tl, gt, pa, sl;
 } Dovat;
 
 typedef int table[50][100];

void readFile( Dovat **a, int *n , int *m){
	int chose =0;
	do{
		printf("Chon cai balo( 1/2/3 )\n");
		scanf("%d", &chose);
	}while(chose != 1 && chose != 2 && chose != 3);
	char filename[25];
	if( chose ==1){
		FILE *f =  fopen("QHD_CaiBalo.inp", "r");
		(*a) = (Dovat*)malloc(sizeof(Dovat));
		fscanf(f, "%d", m);
		int i =0;
		while(!feof(f)){
			(*a) = realloc( *a, sizeof(Dovat)*(i+1));
			fscanf(f, "%d %d %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, (*a)[i].name);
			(*a)[i].pa =0;
			(*a)[i].sl = 100;
			i++;
		}
		*n = i;
		printf("1");
		fclose(f);
	}else{
		if(chose ==2){
			FILE *f =  fopen("QHD_CaiBalo2.inp", "r");
			(*a) = (Dovat*)malloc(sizeof(Dovat));
			fscanf(f, "%d", m);
			int i =0;
			while(!feof(f)){
				(*a) = realloc( *a, sizeof(Dovat)*(i+1));
				fscanf(f, "%d %d %d %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt,&(*a)[i].sl, (*a)[i].name);
				(*a)[i].pa =0;
				i++;
			}
			*n = i;
				printf("2");
			fclose(f);
		}else{
				FILE *f =  fopen("QHD_CaiBalo.inp", "r");
				(*a) = (Dovat*)malloc(sizeof(Dovat));
				fscanf(f, "%d", m);
				int i =0;
				while(!feof(f)){
					(*a) = realloc( *a, sizeof(Dovat)*(i+1));
					fscanf(f, "%d %d %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, (*a)[i].name);
					(*a)[i].pa =0;
					(*a)[i].sl = 1;
					i++;
				}
				*n = i;
					printf("3");
				fclose(f);
		}
	}
}

void InPa(Dovat *a, int n , int m){
	int total_val =0, total_weight =0;
	printf("phuong an cai ba lo 1 su ding quy hoach dong:\n");
	printf("|---|---------------------|-----------|-------|---------|\n");
	printf("|%-3s|%-21s|%-11s|%-7s|%-9s|\n", "STT", "     Ten Do Vat", "Trong luong", "Gia tri","Phuong an");
	printf("|---|---------------------|-----------|-------|---------|\n");
	int i, k;
	for( i= 0, k=1; i < n ; i++){
		printf("| %-2d| %-20s|%11d|%7d|%9d|\n", k++, a[i].name, a[i].tl, a[i].gt, a[i].pa);
		total_val += a[i].gt * a[i].pa;
		total_weight += a[i].tl * a[i].pa;
	}
	printf("|---|---------------------|-----------|-------|---------|\n");
	printf("Tong trong luong cua cai balo: %5d\n", m);
	printf("Tong trong luong: %5d\n", total_weight);
	printf("Tong gia tri: %5d\n", total_val);
}

int min( int a, int b){
	if( a< b){
		return a;
	}
	return b;
}

void createTable( Dovat *a, int n, int m, table F, table X){
	int i, j, k;
	for(i =0; i <= m ;i++){
		X[0][i] = min(i/ a[0].tl, a[0].sl);
		F[0][i] = X[0][i]* a[0].gt;
	}
	for( i=1; i <n ; i++){
		for(j =0; j <= m ; j++){
			F[i][j] = F[i-1][j];
			X[i][j] =0;
			int max_pa = min(j/a[i].tl, a[i].sl);
			for(k =1; k <= max_pa; k++){
				if( k*a[i].gt + F[i-1][j- k*a[i].tl] > F[i][j] ){
					F[i][j] = k*a[i].gt + F[i-1][j-k*a[i].tl];
					X[i][j]= k;
				}
			}
		}
	}
}

void printTable(int n, int m, table F, table X){
	printf("Bang quy hoach dong:\n");
	int i, j;
	for(i =0; i < n+4; i++){
		if( i==0 || i==2|| i==n+3){
			printf("|---");
			for( i=0; i <m ; i++){
				printf("|-----");
			}
		}else{
			if(i ==1){
				printf("K\\V");
				for(i=0; i<m;i++){
					printf("|  %-3d", i);
				}
			}else{
				printf("|  %-2d", i+1);
				for(j =0; j < m; j++){
					printf("|  %2d  %2d",F[i][j], X[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

void seachTable(Dovat *a, int n, int m, table X){
	int i;
	for( i = n-1; i>= 0; i--){
		a[i].pa = X[i][m];
		m-= X[i][m]* a[i].tl;
	}
}
int main (){
int n =0, m =0;
Dovat *a;
table F,X;readFile(&a,&n,&m);
createTable(a,n,m,F,X);
printTable(n,m,F,X);
seachTable(a,n,m ,X);
InPa(a,n,m);
free(a);
}
