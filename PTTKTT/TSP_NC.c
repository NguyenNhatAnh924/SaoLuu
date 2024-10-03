#include <stdio.h>
#include "stdlib.h"
#define MIN_F 3.4e38
#define size 30

typedef struct{
	float length;
	int first, last;
	int dung;
}Canh;

typedef struct{
	int n;
	Canh a[size][size];

}DoThi;

void readFile(DoThi *G)
{
	FILE *f = fopen("TSP1.txt","r");
	fscanf(f,"%d", &G->n);
	int i, j;
	for(i=0 ; i< G->n; i++){
		for(j=0 ; j< G->n; j++){
			fscanf(f, "%f",&G->a[i][j].length);
			G->a[i][j].first= i;
			G->a[i][j].last =j;
			G->a[i][j].dung = 0;
		}
	}
	fclose(f);	
}

void InDT( DoThi *G)
{
	int i, j;
	for(i= 0; i < G->n; i++){
		for( j = 0; j< G->n; j++){
			printf(" %c%c= %-1.1f ",G->a[i][j].first + 97, G->a[i][j].last + 97,G->a[i][j].length);
		}
		printf("\n");
	}
}

void InPA(Canh a[], int n)
{
	printf("Phuong an tim dc: \n");
	int i;
	for( i =0; i < n; i++){
		printf("%c%c  %-1.1f\n", a[i].first,a[i].last ,a[i].length);
	}
	float tong=0;
	printf("Chu trinh : \n");
	for ( i=0;i< n; i++){
		printf("%c -> ", a[i].first + 97);
		tong += a[i].length;
	}
	printf("%c ", a[0].first+97);
	printf("\nTong do dai cua chu trinh: %0.1f\n", tong);
}

int isChuTrinh(Canh a[], int n, int next)
{
	int i;
	for( i=0; i<n; i++){
		if( next == a[i].first){
			return 1;
		}
	}
	return 0;
}

float CD (DoThi *G, float cost, int cap)
{
	float canh_min = MIN_F;
	int i, j;
	for(i=0; i< G->n; i++)
	{
		for(j=0; j < G->n; j++)
		{
			if( i != j && !G->a[i][j].dung && G->a[i][j].length < canh_min){
				canh_min = G->a[i][j].length;
			}
		}
	}
	return cost = cost + (G->n -cap)*canh_min;
}

Canh PA[size];

void updatePA (DoThi *G, float cost, float *COST, Canh x[])
{
	int n = G->n;
	x[n-1] = G->a[x[n-2].last][x[0].first];
	cost += x[n -1].length;
	int i;
	if ( cost < *COST)
	{
		*COST = cost;
		for( i=0; i <n ; i++)
		{
			PA[i] = x[i];
		}
	}
}

void nhanhCan(DoThi *G, int i, int current, float p_cost, float *Cost, Canh x[])
{
	int n = G->n;
	int next; 
	for (next =0; next < n; next++)
	{
		if ( current != next && !G->a[current][next].dung && !isChuTrinh(x,i,next))
		{
			float cost, lbound;
			cost = p_cost + G->a[current][next].length;
			lbound = CD(G,cost, i+1);
			if ( cost< *Cost)
			{
				x[i] = G->a[current][next];
				G->a[current][next].dung =1;
				G->a[next][current].dung=1;
				if( i == n-2)
				{
					updatePA(G,cost,Cost,x);
				}else{
					nhanhCan(G,i+1,next,cost,Cost,x);
				}
			}
			G->a[current][next].dung =0;
			G->a[next][current].dung=0;
		}
	}
}

void reset(DoThi *G){
	int i,j;
    for( i = 0; i < G->n; i++){
        for( j = 0; j < G->n; j++){
            G->a[i][j].dung = 0;
        }
    }
}
int main(){
	DoThi a;
	readFile(&a);
	Canh x[size];
	while(1){
		InDT(&a);
		reset(&a);
		float Cost = MIN_F;
		char s;
		do{
			printf("Chonj thanh pho xuat phat: \n");
			scanf("%c", &s);
		}while(s < 'a'|| s > 'e');
		nhanhCan(&a, 0, s- 97,0,&Cost,x);
		InPA(PA, a.n);
		do{
			printf("Tiep tuc (Y/N)?\n");
			scanf("%c",&s);
			if(s== 'n' || s == 'N'){
				return 0;
			}
		}while( s != 'y' || s!= 'Y');
		
	}

	
}
