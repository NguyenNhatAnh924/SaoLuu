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
//kiem tra cung
//int testEdges(int a, int b, Graph G){
//		return a > G.n || b > G.n ? 0 : 1;
//}

//nhap cung bang tay
//void addEdges(Graph *G){
//	int a , b;
//	char chose;
//	do{
//		printf("Nhap cung: \n"); 
//		do{
//		scanf("%d%d", &a,&b);
//			if(!testEdges(a,b,*G)){
//				printf("Cung khong hop le!\nNhap lai!\n");
//			}
//		}
//		while(!testEdges(a,b,*G));
//		G->A[a-1][b-1]++;
//		G->A[b-1][a-1]++;	
//		printf("Tiep tuc??\nY or N\n");
//		scanf("%*c");
//		scanf("%c",&chose);	
//	}
//	while(chose == 'y' || chose =='Y');	
//}

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
//timf bac cua 1 dinh
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
//khai bao stack
typedef struct{
	int data[Max_length];
	int last;
}stack;

//khoi tao stack rong;
void makeNullStcak(stack *stack){
	stack->last =0;
}

//add stack
void insertStack(stack *stack, int x){
	stack->data[stack->last] = x;
	stack->last++;
}

//lay ra khoi stack
int topStack(stack *stack){
	return stack->data[stack->last-1];
}

//xoa 1 phan tu trong stack
void popStack(stack *stack){
	stack->last--;
}

//kiem tra stack rong
int emptyStack(stack stack){
	return stack.last == 0;
}

//Duyet thro chieu sau
List depthFirstSeach(Graph *G, int x){
	stack s;
	makeNullStcak(&s);
	insertStack(&s, x);
	//khoi tao cac dinh chua duoc duyet
	List List_dfs;
	makeNull(&List_dfs);
	int mark[Max_Vertices];
	int i;
	for(i =1; i <= G->n; i++){
		mark[i]=0;
	}
	while(!emptyStack(s)){
		int u = topStack(&s);
		popStack(&s);
		if(mark[u]==1){
			continue;
		}
		insert(&List_dfs,u);
		mark[u] = 1;
		List L = neighbors(*G,u);
		for(i =1; i <= L.size ; i++){
			int v = element_at(&L,i);
			if(mark[v]==0){
				insertStack(&s,v);
			}
		}
	}
	return List_dfs;
}
int main(){
	Graph *G;
	int n = 0;
	int m = 0;
	List l;
	makeNull(&l);
	readFile(&G,&n,&m);
	printGraph(*G);
	int i, j;
	int mark_dfs[Max_Vertices];
	
	for(i=1;i <= G->n; i++){
		mark_dfs[i]=0;
	}
	
	for(i =1; i <= G->n; i++){
		if(mark_dfs[i] == 0){
			List dfs = depthFirstSeach(G,i);
			for(j = 1; j <= dfs.size; j++){
				int k = element_at(&dfs, j);
				printf("Duyet: %d\n", k);
				mark_dfs[k] = 1;
			}
		}
	}

	
	
//	printf("%3s	%3s\n","Dinh","Bac");
//	for( i = 1; i <= G->n; i++ )
//	{
//		printf("%d\t%d\n",i, degree(*G,i));
//	}
//	printf("%3s	%3s\n","Dinh","Neighbors");
//	for( i = 1; i <= G->n; i++ )
//	{
//		printf("%d       ",i);
//		printList(neighbors(*G, i));
//		printf("\n");
//	}
	return 0;
}
