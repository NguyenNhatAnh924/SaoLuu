#include <stdio.h>
#include <stdlib.h>
 #define Max_Vertices 20 
 #define Max_length 100
typedef struct{
	int A[Max_Vertices ][Max_Vertices];
	int n;
}Graph;

typedef struct{
	int data[Max_length];
	int size;
}List;

//tao ds rong
void makeNull(List *l){
	l->size = 0;
}
//them phan tu vao ds
void insert(List *l, int x){
	l->data[l->size] = x;
	l->size++;
}
//lay phan tu tu ds
int element_at(List *l, int i){
	return l->data[i-1];
}

//in ds
void printList(List l){
	int i ;
	for(i = 0 ; i < l.size; i++ )
		printf("%d ", l.data[i]);	
}

//tao ma tran do thi
void createGraph(Graph *G, int n){
	int i ,j;
	G->n = n;
	for( i = 0; i < n; i++){
		for( j = i ; j < n ; j++){
			G->A[i][j] = 0;
			G->A[j][i] =0;
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

//them cung (x;y)
void addEdges(Graph *G, int x, int y ){
	if(x-1 != y-1){
		G->A[x-1][y-1]++;
		G->A[y-1][x-1]++;
	}else{
		G->A[x-1][y-1]++;
	}

}

//kiem tra 2 dinh ke nhau
int adjacent(Graph G, int x, int y){
	return G.A[x-1][y-1] == 1 ? 1 : 0;
}
//tim bac cua 1 dinh
int degree(Graph G, int x){
	int  i, Degree = 0;
	for(i = 0; i < G.n; i++){
		if(x-1 != i){
			Degree += G.A[x-1][i];
		}else{
			Degree += G.A[x-1][i]*2;
		}
		
	}
	return Degree;
}
//doc file
void readFile(Graph **G, int *n, int *m){
	 freopen("buoi1.txt", "r",stdin);
	(*G) = (Graph*)malloc(sizeof(Graph));
	scanf("%d %d", n, m);
	createGraph((*G),*n);
	int i, x, y;
	for( i =0; i < *m ; i++){
		(*G) = realloc(*G,sizeof(Graph)*(i+1));
		scanf("%d%d", &x,&y);
		addEdges((*G),x,y);
	}
}
//tom hang xom
List neighbors(Graph G, int x){
	List l;
	makeNull(&l);
	int i;
	for( i =0; i < G.n ; i++){
		if(adjacent(G,x,i+1)==1){
			insert(&l, i+1);
		}
	}
	return l;
}

//cai dac hang doi
typedef struct{
	int data[Max_length];
	int front, rear;
}Queue;

//khoi tao hang doi
void makeNullQueue(Queue *Q){
	Q->front = -1;
	Q->rear = -1;
}
//them phan tu vao queue
void push_Queue(Queue *Q, int x){
	if(fullQueue(*Q)){
		return;
	}
	if(empty_Queue(*Q)){
		Q->front=0;
	}	
	if(Max_length - 1 == Q->rear){
		int i;
		for(i = Q->front; i <= Q->rear; i++){
			Q->data[i - Q->front] = Q->data[i];
			Q->rear = Q->rear - Q->front;
			Q->front =0;
		}
	}
	Q->rear++;
	Q->data[Q->rear] = x;
}

//Kiem tra rong
int empty_Queue(Queue Q){
	return Q.front == -1;
}

//kiem tra day
int fullQueue(Queue Q){
	return Max_length == (Q.rear - Q.front +1);
}
//lay phan tu
int top_Queue(Queue *Q){
	if(empty_Queue(*Q)){
		return;
	}else{
		return Q->data[Q->front];
	}
}
//xoa phan tu
void deQueue(Queue *Q){
	if(empty_Queue(*Q)){
		return;
	}
	
	if(Q->front==Q->rear){
		makeNullQueue(Q);
	}else{
		Q->front++;
	}
}
//BFS
List BFS(Graph G, int x){
	Queue q;
	makeNullQueue(&q);
	
	int mark[Max_Vertices];
	int i;
	for(i=1; i <= G.n; i++)
		mark[i]= 0;
	
	List List_BFS;
	makeNull(&List_BFS);
	
	push_Queue(&q,x);
	while(!empty_Queue(q)){
		int u = top_Queue(&q);
		deQueue(&q);
		if(mark[u]==1){
			continue;
		}	
		insert(&List_BFS,u);
		mark[u]=1;
		List L;
		makeNull(&L);
		L = neighbors(G, u);
		int v;
		for( i = 1 ; i <= L.size; i++){
			v = element_at(&L,i);
			if(mark[v]==0){
				push_Queue(&q,v);
			}		
		}	
	}
	return List_BFS;
}
//BFS_ 2
List BFS_2(Graph G, int x,int parent[]){
	Queue q;
	makeNullQueue(&q);
	
	int mark[Max_Vertices];
	int i;
	for(i=1; i <= G.n; i++)
		mark[i]= 0;
	
	List List_BFS;
	makeNull(&List_BFS);
	
	push_Queue(&q,x);
	parent[x]=0;
	while(!empty_Queue(q)){
		int u = top_Queue(&q);
		deQueue(&q);
		if(mark[u]==1){
			continue;
		}	
		insert(&List_BFS,u);
		mark[u]=1;
		List L;
		makeNull(&L);
		L = neighbors(G, u);
		int v;
		for( i = 1 ; i <= L.size; i++){
			v = element_at(&L,i);
			if(mark[v]==0){
				push_Queue(&q,v);
				if(parent[v]==-1){
					parent[v]=u;
				}
			}		
		}	
	}
	return List_BFS;
}

//BFS for loop
void BFS_Forloop(Graph G, int x){
	int mark[Max_Vertices];
	int i;
	for(i=1; i <= G.n; i++){
		mark[i]=0;
	}
	
	int u,v;
	for(u = 1; u <= G.n; u++){
		if(mark[u]==0){
			List L;
			makeNull(&L);
			L = BFS(G,u);
			for(i = 1; i <= L.size; i++){
				v = element_at(&L,i);
				printf("%d\n", v);
				mark[v]=1;
			}
		}
	}
}

//tree
void tree(Graph G, int x){
	int parent[Max_Vertices];
	int i;
	for(i = 1; i <= G.n; i++)
		parent[i]=-1;
	
	int mark[Max_Vertices];
	for(i=1; i <= G.n; i++){
		mark[i]=0;
	}
	
	int u,v;
	for(u = 1; u <= G.n; u++){
		if(mark[u]==0){
			List L;
			makeNull(&L);
			L = BFS_2(G,u,parent);
			for(i = 1; i <= L.size; i++){
				v = element_at(&L,i);
				mark[v]=1;
			}
		}
	}
	
	for(i=1; i<= G.n; i++){
		printf("parent[%d]: %d\n",i,parent[i]);
	}
}
int main(){
	Graph *G;
	int n = 0;
	int m = 0;
	readFile(&G,&n,&m);
	List l = neighbors(*G,2);
	printList(l);
	

	return 0;
}
