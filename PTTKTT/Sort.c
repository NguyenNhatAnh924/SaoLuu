#include "stdio.h"
#define Max 100

typedef int keyrtype;
typedef float othertype;

typedef struct {
	keyrtype key;
	othertype other;
}record;

void swap ( record *a, record *b){
	record tam = *a;
	*a = *b;
	*b = tam;
}

void bubbleSort(record a[], int n){
	int i, j;
	for(i=0; i< n-1; i++){
		for( j= n -1; j > i; j--){
			if(a[j].key < a[i].key)
				swap(&a[i], &a[j]);
		}
	}
}

void readFile(record a[], int *n)
{
	FILE *f = fopen("data.txt", "r");
	if (f != NULL){
		while(!feof(f)){
			fscanf(f,"%d %f",&a[*n].key, &a[*n].other);
			(*n)++;
		}
	}
	else
	{
		printf ("loi mo file.\n");
		fclose(f);
	}
}

void selectionSort(record a[], int n){
	int i, j;
	for( i=0; i < n-1 ; i++){
		keyrtype lowkey = a[i].key;
		int lowindex = i;
		for (j = i+1; j < n; j++){
			if( a[j].key < lowkey){
				lowkey = a[j].key;
				lowindex = j;
			}
		}
		swap(&a[i], &a[lowindex]);
	}
}

void insertionSort( record a[], int n){
	int i;
	for (i =0; i < n ; i++){
		int j = i;
		while((j > 0) && a[j].key < a[j -1].key){
			swap(&a[j], &a[j-1]);
			j--;
		}
	}
}

int findPivot(record a[], int i, int j){
	int k;
	keyrtype firstkey = a[i].key;
	for( k = i +1; k <= j ; k++){
		if ( a[k].key != firstkey)
			return a[k].key > firstkey ? k : i;
	}
	return -1;
}

int findPivot1(record a[], int i, int j){
	int k;
	keyrtype firstkey = a[i].key;
	for( k = i +1; k <= j ; k++){
		if ( a[k].key != firstkey)
			return a[k].key < firstkey ? k : i;
	}
	return -1;
}

int patation(record a[],int L, int R, keyrtype pivot){
	while( L <= R){
		while ( a[L].key < pivot)
			L++;
		
		while ( a[R].key >= pivot)
			R--;
			
		if (L < R){
			swap(&a[L], &a[R]);
		}
	}
	return L;
}

int patation1(record a[],int L, int R, keyrtype pivot){
	while( L <= R){
		while ( a[L].key <= pivot)
			L++;
		
		while ( a[R].key > pivot)
			R--;
			
		if (L < R){
			swap(&a[L], &a[R]);
		}
	}
	return L;
}

void quickSort(record a[],int i, int j){
	int pivotindex = findPivot(a,i,j);
	if(pivotindex != -1){
		int k = patation(a,i,j,a[pivotindex].key);
		quickSort(a,i, k-1);
		quickSort(a,k,j);
	}
}


void pusdow(record a[], int first, int last){
	int f = first;
	while( f <= (last -1)/2){
		int L =2* f+1;
		int R = 2*f+2;
		if(last == L){
			if(a[f].key > a[L].key){
				swap(&a[f], &a[L]);
			}else{
				return;
			}
		}
		
		if((a[f].key > a[L].key) && ( a[L].key <= a[R].key)){
			swap(&a[f], &a[L]);
			f= L;
		}else {
			if((a[f].key > a[R].key) && (a[R].key < a[L].key)){
				swap(&a[f], &a[R]);
				f =R;
			}else{
				return;
			}
		}
	}
}

void heapSort( record a[], int n){
	int i;
	for ( i = (n-2)/2; i >=0 ; i--){
		pusdow(a,i,n-1);
	}
	for(i = n-1; i >= 2 ; i--){
		swap(&a[0], &a[i]);
		pusdow(a, 0, i-1);
	}
	swap(&a[0], &a[1]);
}
void printData( record a[], int n){
	int i;
	printf("%4s  %5s  %8s \n", "STT", "Key", "Other");
	for ( i=0; i< n; i++){
	
		printf("%3d  %5d  %8.1f \n", i+1, a[i].key , a[i].other);
	}
}

int main(){
	
// bubble
//	record a[Max];
//	int n =0;
//	printf("Thuat toan bubbleSort\n");
//	readFile(a, &n);
//	printf("DL truoc khi sap xep:\n");
//	printData(a, n);
//	bubbleSort(a, n);
//	printf("DL sau khi sap xep:\n");
//	printData(a, n);

//	select
//	record a[Max];
//	int n =0;
//	printf("Thuat toan selectionSort\n");
//	readFile(a, &n);
//	printf("DL truoc khi sap xep:\n");
//	printData(a, n);
//	selectionSort(a, n);
//	printf("DL sau khi sap xep:\n");
//	printData(a, n);


//	insert
//	record a[Max];
//	int n =0;
//	printf("Thuat toan insertionSort\n");
//	readFile(a, &n);
//	printf("DL truoc khi sap xep:\n");
//	printData(a, n);
//	insertionSort(a, n);
//	printf("DL sau khi sap xep:\n");
//	printData(a, n);


//	quick	
//	record a[Max];
//	int n =0;
//	printf("Thuat toan insertionSort\n");
//	readFile(a, &n);
//	printf("DL truoc khi sap xep:\n");
//	printData(a, n);
//	quickSort(a,0,n-1);
//	printf("DL sau khi sap xep:\n");
//	printData(a, n);

//	quick bien di
	record a[Max];
	int n =0;
	printf("Thuat toan insertionSort\n");
	readFile(a, &n);
	printf("DL truoc khi sap xep:\n");
	printData(a, n);
	quickSort(a,0,n-1);
	printf("DL sau khi sap xep:\n");
	printData(a, n);

//	heap
//	record a[Max];
//	int n =0;
//	printf("Thuat toan insertionSort\n");
//	readFile(a, &n);
//	printf("DL truoc khi sap xep:\n");
//	printData(a, n);
//	heapSort(a,n);
//	printf("DL sau khi sap xep:\n");
//	printData(a, n);

return 0;
}
