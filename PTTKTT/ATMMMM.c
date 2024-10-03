#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char ten[25];
	int mg, PA;
}Tien;

void swap( Tien *a, Tien *b){
	Tien tmp = *a;
	 *a = *b;
	  *b = tmp;
}

void sort( Tien *m , int n){
int i, j;
for(i =0; i < n-1; i++){
	for(j = i+1; j < n; j++){
		if(m[i].mg < m[j].mg)
			swap(&m[i], &m[j]);
	}
}
}

void readFlie(Tien **m, int *n){
	FILE *f  = fopen("ATM.txt", "r");
	(*m) = (Tien*)malloc(sizeof(Tien));
	int i =0;
	while(!feof(f)){
		(*m) = realloc(*m,sizeof(Tien)*(i +1));
		fscanf(f, "%d %[^\r\n]s", &(*m)[i].mg, &(*m)[i].ten);
		(*m)[i].ten[strlen((*m)[i].ten) -1]= '\0';
		(*m)[i].PA = 0;
		i++;
	}
	(*n)= i;
	fclose(f);
}

void inPA( Tien *m, int n, int t){
	printf("|---|----------------------|-----------|----------|----------|\n");
	printf("|%-3s| %-21s|%10s |%-10s|%-10s|\n","STT", " LOAI", "MG", " PA", "THANH TIEN");
	printf("|---|----------------------|-----------|----------|----------|\n");
	int i, k;
	int total =0;
	for(i =0, k=1; i < n ; i++){
		printf("|%-3d| %-20s |%-10d |%-10d|%-10d|\n", k++, m[i].ten, m[i].mg, m[i].PA, m[i].PA * m[i].mg);
		total += m[i].PA * m[i].mg;
	}
	printf("|---|----------------------|-----------|----------|----------|\n");
	printf("So tien can rut la: %-9d\nSo tien da tra la: %-9d\nSo tien chua tra la: %-9d", t, total, t - total);
}

void greedy(Tien *m, int n , int t){
	int i =0;
	while(i < n && t > 0){
		m[i].PA = t / m[i].mg;
		t-= m[i].mg * m[i].PA;
		i++;
	}
}
int main(){
	int n = 0;
	int t=1299990;
	Tien *m;
	readFlie(&m, &n);
	sort(m, n);
	greedy(m,n,t);
	inPA(m,n,t);
	free(m);
}
