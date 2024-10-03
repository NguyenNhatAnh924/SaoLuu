#include"stdio.h"
#include"conio.h"
#include"malloc.h"
#include"String.h"

typedef struct{
	char ten[25];
	int sl, mg;
}tien;

void readFlie(tien **m,int *n){
	FILE *f = fopen("ATM.txt","r");
	*m = (tien*)malloc(sizeof(tien));
	int i=0;
	while(!feof(f)){
		(*m) = (tien*)realloc(*m, sizeof(tien)*(i+1));
		fscanf(f,"%d %[^\r\n]s",&(*m)[i].mg,&(*m)[i].ten);
		(*m)[i].ten[strlen((*m)[i].ten)-1]= '\0';
		(*m)[i].sl = 0;
		i++;
	}
	*n=i;
	fclose(f);
}

void inDS(tien *m, int n, int t){
	int tong =0;
	printf("|----|---------------------|----------|-------|-----------|\n");
	printf("|%-3s|%-21s|%-10s|%-7s|%-10s|\n"," STT","  Loai tien","  Menh Gia","  So to"," Thanh Tien");
	printf("|----|---------------------|----------|-------|-----------|\n");
	int i=0;
	for (i=0; i<n ; i++){
		printf("|  %-2d| %-20s| %-9d|  %-5d|   %-8d|\n", i+1, m[i].ten, m[i].mg, m[i].sl, m[i].sl*m[i].mg );
		tong+= m[i].mg*m[i].sl;
	}
	printf("|----|---------------------|----------|-------|-----------|\n");
	printf("So tien can rut: %-9d\n", t);
	printf("So tien da tra: %-9d\n", tong);
	printf("So tien chua tra: %-9d\n",t-tong);
}

void Swap(tien *a, tien *b){
	tien tam= *a;
	*a = *b;
	*b = tam;
}

void sort(tien *m, int n){
	int i, j;
	for (i =0; i< n-1; i++){
		for(j = i+1; j< n; j++){
			if (&m[i].mg < &m[j].mg){
				Swap(&m[i], &m[j]);
			}
		}
	}
}

void greedy (tien *m, int n, int t){    
    int i = 0;
    while (i < n && t > 0) {
        m[i].sl = t / m[i].mg;
        t -= m[i].sl*m[i].mg;
        i++;
    }    
}

int main(){
    tien *m;
    int n = 0, t;
    readFlie(&m, &n);    
    printf("Nhap so tien can rut: ");
    scanf("%d", &t);
    sort(m, n);
    greedy(m, n, t);
    inDS(m, n, t);
    free(m);
}
