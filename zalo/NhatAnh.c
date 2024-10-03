#include<stdio.h>
typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfileds;
}recordtype;
void Swap(recordtype *x,recordtype *y){
	recordtype temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
//void read_data(recordtype a[], int* n){
//	FILE *f;
//	f = fopen("data.txt","r");
//	int i=0;
//	if (f!=NULL){
//		while(!feof(f)){
//			fscanf(f,"%d%f",&a[i].key, &a[i].otherfileds);
//			i++;
//		}
//	}else 
//		printf(" loi mo file\n");
//	
//	fclose(f);
//	*n =i; 
//}

void read_Data(recordtype a[] , int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if(f!= NULL)
	while(!feof(f)){
		fscanf(f,"%d%f", &a[i].key, &a[i].otherfileds);
		i++;
	} else printf("Loi mo file\n");
	fclose(f);
	*n=i;	
}

void selectionSort(recordtype a[],int n){
	int i,j,lowindex;
	keytype lowkey;
	for(i=0;i<=n-2;i++){
		lowkey=a[i].key;
		lowindex=i;
		for(j=i+1;j<=n-1;j++)
		if(a[j].key<lowkey){
			lowkey=a[j].key;
			lowindex=j;
		}
		Swap(&a[i],&a[lowindex]);
	}
}
void Insertionsort(recordtype a[],int n){
	int i,j;
	for(i=1;i<=n-1;i++){
		j=i;
		while(j>0&&a[j].key<a[j-1].key){
			Swap(&a[j],&a[j-1]);
			j--;
		}
	}
}
void BubbleSort(recordtype a[],int n){
	int i,j;
	for(i=0;i<=n-2;i++)
	for (j=n-1;j>=i+1;j--)
	if(a[j].key<a[j-1].key)
	Swap(&a[j],&a[j-1]);
}
int FindPivot(recordtype a[],int i,int j){
	keytype firstkey;
	int k;
	k=i+1;
	firstkey=a[i].key;
	while(k<=j && a[k].key == firstkey)k++;
	if(k>j)return -1;
	if(a[k].key>firstkey)return k;
	return i;
}

int Partition( recordtype a[], int i, int j , keytype pivot){
	int L, R;
	L= i;
	R = j;
	while(L<= R){
		while( a[L].key < pivot){
			L++;
		}
		
		while( a[R].key >= pivot){
			R--;
		}
		
		if(L<R){
			Swap(&a[L], &a[R]);
		}
		
	}
	return L;
}

void QuickSort(recordtype a[], int i,int j)
{ keytype pivot;
  int pivotindex, k;
  pivotindex = FindPivot(a,i,j);
  if (pivotindex != -1) {
      pivot = a[pivotindex].key;
      k = Partition(a,i,j,pivot);
      QuickSort(a,i,k-1);
      QuickSort(a,k,j);
  }
}

//void PushDown(recordtype a[ ], int first,int last)
//{ int  r= first;
//  while (r <= (last-1)/2)
//   if (last == 2*r+1) {
//     if (a[r].key > a[last].key) Swap(&a[r],&a[last]);
//     r = last;
//   } else
//   if ((a[r].key>a[2*r+1].key) && (a[2*r+1].key<=a[2*r+2].key))
//   {
//      Swap(&a[r],&a[2*r+1]);
//      r = 2*r+1 ;
//   } else
//      if ((a[r].key>a[2*r+2].key) && (a[2*r+2].key<a[2*r+1].key))
//      {
//	 Swap(&a[r],&a[2*r+2]);
//	 r = 2*r+2 ;
//      }
//      else
//	 r = last;
//}

void PushDown(recordtype a[ ], int first,int last)
{ int  r= first;
  while (r <= (last-1)/2)
   if (last == 2*r+1) {
     if (a[r].key < a[last].key) Swap(&a[r],&a[last]);
     r = last;
   } else
   if ((a[r].key<a[2*r+1].key) && (a[2*r+1].key>=a[2*r+2].key))
   {
      Swap(&a[r],&a[2*r+1]);
      r = 2*r+1 ;
   } else
      if ((a[r].key<a[2*r+2].key) && (a[2*r+2].key>a[2*r+1].key))
      {
	 Swap(&a[r],&a[2*r+2]);
	 r = 2*r+2 ;
      }
      else
	 r = last;
}

void HeapSort(recordtype a[], int n)
      { 
	   int i;
    for (i = (n-2)/2; i>=0; i--)
	PushDown(a, i, n-1);
   for (i = n-1; i>=2; i--) {
	Swap(&a[0],&a[i]);
		PushDown(a, 0, i-1);
          }
   Swap(&a[0],&a[1]);
      }

void Print_Data(recordtype a[], int n){
	int i;
	for(i = 0; i<n; i++)
	printf("%3d%5d%8.2f\n", i+1, a[i].key, a[i].otherfileds);
}
	int main(){
			
//	recordtype a[]=
//		{
//		{50 ,9.3},
//		{10 ,20.5},
//		{143 ,3.28},
//		{0 ,14.12},
//		{10 ,30.5},
//		{120 ,9.90},
//		{90 ,56.7},
//		{10 ,4.22},
//		{90 ,26.4},
//		{140 ,12.15},
//		{20 ,1.84},
//		{30 ,0.75}	
//		};
//		int n = sizeof(a) / sizeof(a[0]);
//		printf("Sau sap xep\n");
//		selectionSort(a,n);
//		Print_Data(a, n);
		
		
		recordtype a[100];
		int n;
//		printf("--chon--\n");
//		read_Data(a,&n);
//		printf("--ban dau--\n");
//		Print_Data(a, n);	
//		selectionSort(a,n);
//		printf("--Sau chon--\n");	
//		Print_Data(a, n);
		
//		printf("--xen-\n");
//		read_Data(a,&n);
//		printf("--ban dau--\n");
//		Print_Data(a, n);	
//		Insertionsort(a,n);
//		printf("--Sau xen--\n");	
//		Print_Data(a, n);

//		printf("--bot-\n");
//		read_Data(a,&n);
//		printf("--ban dau--\n");
//		Print_Data(a, n);	
//		BubbleSort(a,n);
//		printf("--Sau bot--\n");	
//		Print_Data(a, n);

//		printf("-- Nhanh-\n");
//		read_Data(a,&n);
//		printf("--ban dau--\n");
//		Print_Data(a, n);	
//		QuickSort(a,0, n-1);
//		printf("--Sau Nhanh--\n");	
//		Print_Data(a, n);

		printf("-- Vun dong-\n");
		read_Data(a,&n);
		printf("--ban dau--\n");
		Print_Data(a, n);	
		HeapSort(a,n);
		printf("--Sau Vun dong--\n");	
		Print_Data(a, n);
	}
	

