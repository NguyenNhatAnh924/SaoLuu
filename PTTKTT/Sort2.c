#include <stdio.h>

#define Max 100

typedef int keytype;
typedef float othertype;

typedef struct {
	keytype key;
	othertype other;
}record;

void swap ( record *a, record *b){
	record tmp = *a;
	*a = *b;
	*b = tmp;
}

void readFile(record a[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f != NULL){
		while(!feof(f)){
			fscanf(f, " %d %f", &a[*n].key, & a[*n].other);
			(*n)++;
		}
	}else{
		printf("Loi mo file\n");
	}
	fclose(f);
}

void printData(record a[], int n){
	int i;
	printf("%3s   %5s  %8s\n", "STT", "Key ", "Other ");
	for(i=0; i < n ;i++){
		printf("%3d  %5d  %8.1f\n", i+1, a[i].key,a[i].other);
	}
}

void bubbleSort( record a[], int n){
	int i, j;
	for(i = 0; i < n-1; i ++){
		for(j = n-1; j > i; j--){
			if(a[j].key < a[i].key)
				swap(&a[i],&a[j]);
		}
	}
}

void selectionSort(record a[], int n){
	int i,j;
	for(i =0; i< n-1 ; i++){
		keytype lowkey = a[i].key;
		int lowindex = i;
		for( j = i+1; j < n ; j ++){
			if(a[j].key < lowkey){
				lowkey = a[j].key;
				lowindex = j;
			}
		}
		swap(&a[i], &a[lowindex]);
	}
}

void insertionSort( record a[], int n){
	int i;
	for( i =0; i < n ; i++){
		int j = i;
		while((j > 0) && a[j].key < a[j-1]. key){
			swap(&a[j], & a[j-1]);
			j--;
		}
	}
}

int findPivot( record a[], int i, int j){
	int k;
	keytype firstkey = a[i].key;
	for( k = i + 1; k <= j; k++){
		if(a[k].key != firstkey){
			return a[k].key > firstkey ? k : i;
		}
	}
	return -1;
}

int patation(record a[], int L, int R, keytype pivot){
	while(L <= R){
		while(a[L].key < pivot )
			L++;
		
		while (a[R].key >= pivot)
			R--;
		
		if(L < R)
			swap(&a[L], &a[R]); 
	}
	return L;
}

void quickSort(record a[], int i, int j){
	int pivotindex = findPivot(a, i, j );
	if(pivotindex != -1){
		int k = patation(a, i, j, a[pivotindex].key);
		quickSort(a, i, k-1);
		quickSort(a, k, j);	
	}
}

void pushDown( record a[], int first , int last){
	int f = first;
	while( f <= (last -1)/2){
		int L = f*2+1;
		int R = f*2+2;
		if(L == last){
			if(a[f].key > a[L].key)
				swap(&a[f], & a[L]);
			return;
		}
		
		if((a[f].key > a[L].key) && ( a[L].key <= a[R].key)){
			swap(&a[f], &a[L]);
			f=L;
		}
		else if( (a[f].key > a[R].key) && ( a[R].key < a[L].key)){
			swap(&a[f],&a[R]);
			f = R;
		}
		else return;
	}
}

void heapSort(record a[], int n){
	int i;
	for( i = (n -2)/ 2; i >= 0 ; i--)
		pushDown(a,i,n-1);
	
	for( i = n -1; i >= 2 ; i--){
		swap(&a[0], &a[i]);
		pushDown(a, 0, i-1);
	}
	swap(&a[0],&a[1]);
}

void printData1(record a[], int n, int m){
	int i;
	printf("%3s   %5s  %8s\n", "STT", "Key ", "Other ");
	if(n < m){
		for( i =0; i < m ; i++){
			printf("%3d  %5d  %8.1f\n", i+1, a[i].key,a[i].other);
		}
	}
	else for(i =n-1; i >= m ; i--){
			printf("%3d  %5d  %8.1f\n", n-1, a[i].key,a[i].other);
	}
}
int main(){
	record a[Max];
	int n =0;
	printf("DL truoc khi sap xep\n");
	readFile(a, &n);
	printData(a, n);
	printf("DL sau khi sap xep\n");
	heapSort(a,n);
	printData1(a,n,0);
	return 0;
}
