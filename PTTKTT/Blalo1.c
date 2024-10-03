#include"stdio.h"
#include"conio.h"
#include"malloc.h"
#include"String.h"

typedef struct{
	char ten[25];
	float tl, gt, dg;
	int soDV;
}DoVat;

void readFile(DoVat **m, int *n, float *w){
	FILE *f = fopen("CaiBalo1.txt","r");
	(*m) = (DoVat*)malloc(sizeof(DoVat));
	fscanf(f," %f",w);
	int i=0;
	while(!feof(f)){
		(*m) = realloc(*m, sizeof(DoVat)*(i+1));
		fscanf(f,"%f %f %[^\r\n]s", &(*m)[i].tl, &(*m)[i].gt, &(*m)[i].ten);
		(*m)[i].ten[strlen((*m)[i].ten)-1]= '\0';
		(*m)[i].dg = (*m)[i].gt / (*m)[i].tl;
		(*m)[i].soDV =0;
		i++;
	}
	*n = i;
	fclose(f);
}

void inDS(DoVat *m, int n){
	printf("|----|---------------------|-------------|--------|-----------|------------|\n");
	printf("|%-3s|%-21s|%-10s|%-7s|%-10s |%-10s|\n"," STT","  Ten do vat","  Trong luong"," Gia tri"," Don gia ", "So luong lay");
	printf("|----|---------------------|-------------|--------|-----------|------------|\n");
	int i=0;
	float tong =0;
	int TL=0;
	for(i; i< n; i++){
		printf("| %-3d| %-20s|   %-8.2f  |   %-5.2f|  %-8.2f |  %-8.2d  |\n", i+1, m[i].ten, m[i].tl, m[i].gt, m[i].dg, m[i].soDV);
		tong += m[i].gt*m[i].soDV;
		TL += m[i].tl*m[i].soDV;
	}
	printf("|----|---------------------|-------------|--------|-----------|------------|\n");
	printf("Tong gia tri lay duoc: %-9.2f\nTong trong luong: %d\n",tong, TL);
}

void Swap(DoVat *a, DoVat *b)
{
	DoVat temp = *a;
	*a = *b;
	*b = temp;
}

void Sort(DoVat *m, int n)
{
	int i, j;
	for ( i=0; i< n-1; i++){
		for(j=i+1; j< n; j++){
			if(m[i].dg < m[j].dg){
				Swap(&m[i], &m[j]);
			}
		}
	}
}

void greedy(DoVat *m, int n, float w )
{
	int i=0;
	while(i < n && w > 0){
		m[i].soDV = w / m[i].tl;
		w -= m[i].tl*m[i].soDV;
		i++;
	}
}
int main(){
    int n = 0;
	float m = 0;
    DoVat *a;
    readFile(&a, &n, &m);
    Sort(a, n);
    greedy(a, n, m);
    inDS(a, n);
    free(a);
}
