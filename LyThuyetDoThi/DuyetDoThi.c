#include "stdio.h"
#include "stdlib.h"
#define Max_Vertices 20
#define Max_Length 100
	
//Dinh nghia hang doi	
typedef struct{
	int data[Max_Length];
	int front , rear;
}Queue;

//Tao hang dooi rong
void makeNullQueue(Queue *q){
	q->front = -1;
	q->rear = -1;
}

//Kiem Tra rong
int empty_Queue( Queue q){
	return q.front == -1;
}

//Kiem tra day
int full_Queue(Queue q){
	return (q.rear - q.front +1) % Max_Length == 0;
}

//them phan tu
void push_Queue(Queue *q, int x){
	if(full_Queue(*q))
		return;
	
	if(empty_Queue(*q))
		q->front = 0;
		
	q->rear = (q->rear +1) % Max_Length;
	q->data[q->rear] = x;	
}

//Xoa phan tu
void de_Queue(Queue *q){
	if(q->front == q->rear){
		makeNullQueue(q);
	}
	else{
		q->front = ( q->front +1) % Max_Length;
	}
}

//Lay phan tu
int front( Queue *q){
	return q->data[q->front];
}

//Dinh nghia danh sach
typedef struct{
	int data[Max_Length];
	int size;
}List;

//Tao ds rong
void makeNullList(List *l){
	l->size = 0;
}

//kiem tra rong
int empty_List(List l){
	return l.size == 0;
}

//kiem tra day
int full_List(List l){
	return l.size == Max_Length;
}

//them phan tu vao ds
void inser_List(List *l, int x){
	if(full_List(*l))
		return;
	
	l->data[l->size] = x;
	l->size++;
}

//xoa phan tu tai vi tri i
void de_List(List *l, int i){
	for( i ; i <= l->size; i++)
		l->data[i-1] = l->data[i];
	
	l->size--;
}
//Lay phan tu tai vi tri thu i
int element_at(List *l, int i){
	return l->data[i-1];
}
//in ds
void print_List(List l){
	int i =0;
	for( i = 0; i < l.size; i++)
		printf("%d  ", l.data[i]);
}


//dinh nghia do thi
typedef struct{
	int A[Max_Vertices][Max_Vertices];
	int n;
}Graph;

//Tao ma tran 
void create_Graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i =0; i < n ; i++){
		for(j =0 ; j < n; j++){
			G->A[i][j] = 0;
		}
	}
}

//in ma tran do thi
void printGraph(Graph G){
	int i , j;
	for( i =0; i < G.n ; i++){
		for(j = 0 ; j < G.n ; j++){
			printf(" %d\t", G.A[i][j]);
		}
		printf("\n");
	}
}

//them cung
void addEdges(Graph *G, int x, int y){
	if(x != y){
		G->A[x-1][y-1]++;
		G->A[y-1][x-1]++;
	}
	else{
		G->A[x-1][y-1]++;
	}
}

//kiem tra lien ke
int adjacent(Graph G, int x, int y){
	return G.A[x-1][y-1]==1;
}

//tim bac cua din x
int degree(Graph G, int x){
	int degree = 0;
	int i;
	for(i=0; i < G.n; i++){
		if(x-1 == i){
			degree+= G.A[x-1][i]*2;
		}
		else{
			degree += G.A[x-1][i];
		}
	}
	return degree;
}
//tim hang xom
List neighbors(Graph G, int x){
	List a;
	makeNullList(&a);
	int i=0;
	for(i=0;i < G.n ;i++){
		if(adjacent(G,x,i+1)==1){
			inser_List(&a,i+1);
		}	
	}
	return a;
}

//doc file
void redFile(Graph **G, int *n, int *m){
	freopen("buoi1.txt","r",stdin);
	(*G )= (Graph*)malloc(sizeof(Graph));
	scanf("%d %d", n,m);
	create_Graph((*G), *n);
	
	int i, x,y;
	for(i=0; i < *m; i++){
		(*G) = realloc(*G, sizeof(Graph)*(i+1));
		scanf("%d %d", &x, &y);
		addEdges((*G), x, y);
	}
	printf("\n %d\n", *m);
}

int main(){
	Graph *G;
	int n=0,m=0;
	redFile(&G,&n,&m);
	List l = neighbors(*G,2);
	printGraph(*G);
	printf("\n");
	print_List(l);
}
