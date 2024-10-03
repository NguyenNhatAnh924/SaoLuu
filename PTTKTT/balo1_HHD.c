#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char ten[20];
	int tl, gt, soDV;
}DoVaT;

typedef int table[50][100];

void readFile(DoVaT **a, int *n, int *m){
	FILE *f = fopen("QHD_CaiBalo.inp", "r");
	(*a) = (DoVaT*)malloc(sizeof(DoVaT));
	fscanf(f, "%d",m);
	int i=0;
	while(!feof(f)){
		(*a) = realloc(*a, sizeof(DoVaT)*(1+i));
		fscanf(f, "\n %d %d %[^\r\n]s", &(*a)[i].tl, &(*a)[i].gt, &(*a)[i].ten);
		(*a)[i].soDV =0;
		i++;
	}
	*n =i;
	fclose(f);
}

void inPA (DoVaT *a, int n, int m)
{
    int total_val = 0, total_weight = 0;
    printf("Phuong an Cai balo 1 su dung Quy hoach dong:\n");
    printf("|---|---------------------|-----------|-------|---------|\n");
	printf("|%-3s|%-21s|%-11s|%-7s|%-9s|\n", "STT", "     Ten do vat", "Trong luong", "Gia tri", "Phuong an");
	printf("|---|---------------------|-----------|-------|---------|\n");
	int i,k;
	for( i = 0, k = 1; i < n; i++){        
        printf("| %-2d| %-20s|%11d|%7d|%9d|\n", k++, a[i].ten, a[i].tl, a[i].gt, a[i].soDV);
        total_val += a[i].gt*a[i].soDV;
        total_weight += a[i].tl*a[i].soDV;
	}
	printf("|---|---------------------|-----------|-------|---------|\n");	
    printf("Trong luong cua ba lo = %5d\n", m);
    printf("Tong trong luong      = %5d\n", total_weight);
    printf("Tong gia tri          = %5d\n", total_val);
}

void createTable(DoVaT *a, int n, int m,table F, table X)
{
	int i, j, k;
	for ( i=0; i <= m; i++)
	{
		X[0][i] = i/a[0].tl;
		F[0][i] = X[0][i] * a[0].tl;
	}
	
	for( i=1; i <n ; i++)
	{
		for( j =0; j <= m; j++)
		{
			F[i][j] = F[i-1][j];
			X[i][j]=0;
			int max_qty = j/a[i].tl;
			for ( k =1; k <= max_qty; k++)
			{
				if(k*a[i].gt + F[i-1][j-k*a[i].tl] > F[i][j])
				{
					F[i][j] = k* a[i].gt + F[i-1][j-k*a[i].tl];
					X[i][j] =k;
				}
			}
		}
	}
}

void printtable(int n, int m, table F, table X){
	printf("Bang huy hoach dong:\n");
	int i, j;
	for( i =0; i < n+4; i++){
		if(i == 0|| i == 2|| i == n+3){
			printf("|---");
			for(i = 0; i <= m; i++){
				printf("-------|");
			}
		}else{
			if( i== 1){
				printf("|k\\V");
			for( i =0; i <= m; i++){
				printf("|  %-3d", i);
			}
			}else{
				printf("|  %-2d", i+1);
				for( j=0; j <= m;j++){
					printf("|%2d %2d",F[i][j], X[i][j]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}

void serchTable(DoVaT *a, int n , int m, table X){
	int i;
	for(i = n-1;i >= 0; i--){
		a[i].soDV = X[i][m];
		m -= X[i][m] * a[i].tl;
	}
}
int main(){
	int n=0, m=0;
	DoVaT *a;
	table F, X;
	readFile(&a,&n,&m);
	createTable(a,n,m,F,X);
	printtable(n,m,F,X);
	serchTable(a,n,m,X);
	inPA(a,n,m);
	free(a);
}
