#include "stdio.h"
#define MAX_VERTICES 100
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
typedef struct {
int n; /* n: so dinh */
/* ma tran dinh – dinh */
int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

/* Khoi tao do thi G co n dinh */
void init_graph(Graph* G, int n) {
int i, j;
G->n = n;
for (i = 1; i <= n; i++)
for (j = 1; j <= n; j++)
G->A[i][j] = 0;
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
G->A[x][y] = 1; //y ke v?i x
G->A[y][x] = 1; //x ke voi y
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
return G->A[x][y] != 0;
}

/* Tinh bac cua dinh x: deg(x) */
int degree(Graph* G, int x) {
int y, deg = 0;
for (y = 1; y <= G->n; y++)
if (G->A[x][y] > 0)
deg++;
return deg;
}

/* KHAI BAO VA DINH NGHIA CTDL DANH SACH */
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
int size;
} List;
/* Tao danh sach rong */
void make_null(List* L) {
L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
L->data[L->size] = x;
L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1
*/
ElementType element_at(List* L, int i) {
return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
return L->size;
}
void swap(ElementType* a, ElementType* b){
	ElementType tmp = *a;
	*a = *b;
	*b = tmp;
}
//sap xep
void sort(List* L)
{
	int i,j;
	for(i=0;i<L->size-1;i++){
		for(j=i+1;j<L->size;j++){
			if(L->data[i] > L->data[j]){
				swap(&L->data[i], &L->data[j]);
			}
		}
	}
}
/*****************************************/

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
int y;
List list;
make_null(&list);
for (y = 1; y <= G->n; y++)
if (adjacent(G, x, y))
push_back(&list, y);
return list;
}

/* Khai bao Stack*/
#define MAX_ELEMENTS 100
typedef struct {
int data[MAX_ELEMENTS];
int size;
} Stack;
void make_null_stack(Stack* S) {
S->size = 0;
}
void push(Stack* S, int x) {
S->data[S->size] = x;
S->size++;
}
int top(Stack* S) {
return S->data[S->size - 1];
}
void pop(Stack* S) {
S->size--;
}
int empty(Stack* S) {
return S->size == 0;
}

/* Duyet do thi theo chieu sau */
void depth_first_search(Graph* G, int k) {
	Stack L;
	make_null_stack(&L);
	int j;
	push(&L, k); 
	while (!empty(&L)) {
		int x = top(&L); pop(&L);
		if (mark[x] != 0)
		continue;
		mark[x] = 1; 
		List list = neighbors(G, x);
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			push(&L, y);
		}
	}
}

//cay duyet do thi DFS dung ngan xep
void depth_first_search_tree(Graph* G, int k) {
	Stack L;
	make_null_stack(&L);
	int j;
	push(&L, k); 
	parent[k] = 0;
	while (!empty(&L)) {
		int x = top(&L); pop(&L);
		if (mark[x] != 0)
			continue;
		mark[x] = 1; 
		List list = neighbors(G, x);
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if(mark[y] == 0 ){
				parent[y] = x;
				push(&L, y);
			}
		}
	}
}
//###########################//
/* Khai bao Queue */
#define MAX_ELEMENTS 100
typedef struct {
int data[MAX_ELEMENTS];
int front, rear;
} Queue;

void make_null_queue(Queue* Q) {
Q->front = 0;
Q->rear = -1;
}

void push_Q(Queue* Q, int x) {
Q->rear++;
Q->data[Q->rear] = x;
}
int top_Q(Queue* Q) {
return Q->data[Q->front];
}
void pop_Q(Queue* Q) {
Q->front++;
}
int empty_Q(Queue* Q) {
return Q->front > Q->rear;
}

/* Duy?t d? th? theo chi?u r?ng */
void breath_first_search(Graph* G, int k) {
	Queue L;
	make_null_queue(&L);
	parent[k]=0;
	int j;
	push_Q(&L, k);
	while (!empty_Q(&L)) {
		int x = top_Q(&L); pop_Q(&L);
		if (mark[x] != 0) 
			continue;
		printf("%d\n", x);
		mark[x] = 1;
		List list = neighbors(G, x);
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			push_Q(&L, y);
		}
	}
}
//cay duyet do thi BFS
void breath_first_search_tree(Graph* G, int k) {
	Queue L;
	make_null_queue(&L);
	parent[k]=0;
	int j;
	push_Q(&L, k);
	while (!empty_Q(&L)) {
		int x = top_Q(&L); pop_Q(&L);
		if (mark[x] != 0) 
			continue;
		mark[x] = 1;
		List list = neighbors(G, x);
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if(y!=1 && parent[y]== -1){
				parent[y]=x;
				push_Q(&L, y);
			}
		}
	}
}

/* Duy?t d? quy d?nh x */
void traversal(Graph* G, int x) {
	if (mark[x] == 1)
		return;
	printf("%d\n", x);
	mark[x] = 1;
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		traversal(G, y);
	}
}

//cay duyet do thi
void traversal_tree(Graph* G, int x, int p) {
	if (mark[x] == 1)
		return;
	mark[x] = 1;
	parent[x]=p;
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		traversal_tree(G, y, x);
	}
}

void depth_first_search_Dequy(Graph* G, int k) {
	traversal(G, k);
}

void depth_first_search_Dequy_tree(Graph* G, int k) {
	traversal_tree(G , k, 0);
}

//duyet theo chieu rong
//int main(){
//	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
//	Graph G;
//	int n, m, u, v, w, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//
//	int i;
//	for(i=1; i<=G.n; i++){
//		mark[i] = 0;
//	}
//	
//	for(i =1; i <= G.n; i++ ){
//		if(mark[i] == 0){
//			breath_first_search(&G,i, mark);
//		}
//	}
//	
//	return 0;
//}
//
//duyet theo chieu sau de quy
//int main(){
//	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
//	Graph G;
//	int n, m, u, v, w, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//	int i;
//	for(i=1; i<=G.n; i++){
//		mark[i] = 0;
//	}	
//	
//	for(w =1; w <= G.n ;w++){
//		if(mark[w] == 0){
//			depth_first_search_Dequy(&G, w);
//		}
//	}	
//}
//
//duyet theo chieu sau dung ngan xep
//int main(){
//	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
//	Graph G;
//	int n, m, u, v, i, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//	
//	for(i=1; i <= G.n; i++)
//		mark[i] = 0;
//	
//	for(i=1; i <= G.n; i++){
//		if(mark[i]==0)
//			depth_first_search(&G,i);
//	}
//	return 0;
//}
//
//cay duyet do thi BFS dung ngan xep
//int main(){
//	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
//	Graph G;
//	int n, m, u, v, i, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//	
//	for(i=1;i<=G.n;i++){
//		mark[i]=0;
//		parent[i]=-1;
//	}
//	
//	for(i=1;i<=G.n;i++){
//		if(mark[i]==0){
//			depth_first_search(&G,i);
//		}
//	}
//	
//	for(i=1; i<= G.n; i++){
//		printf("%d %d\n", i, parent[i]);
//	}
//	
//	return 0;
//}
//
//cay duyet do thi DFS dung de quy
//int main(){
//	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
//	Graph G;
//	int n, m, u, v, i, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//	
//	for(i=1;i<=G.n;i++){
//		mark[i]=0;
//		parent[i]=-1;
//	}
//	
//	for(i=1;i<=G.n;i++){
//		if(mark[i]==0){
//			depth_first_search_Dequy_tree(&G,i);
//		}
//	}
//	
//	for(i=1; i<= G.n; i++){
//		printf("%d %d\n", i, parent[i]);
//	}
//	
//	return 0;
//}
//
//do thi lien thong
int main(){
		freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, i, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i=1; i<=G.n;i++)
		mark[i]=0;
	
	depth_first_search(&G,1);
	
	e = 0;
	for(i=1;i<=G.n;i++)
		if(mark[i]==1)
			e++;
			
	if(e==G.n){
		printf("YES");
	}else{
		printf("NO");
	}
		
	return 0;
}

