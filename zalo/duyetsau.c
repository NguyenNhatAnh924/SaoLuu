#include "stdio.h"
#define MAX_VERTICES 100
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
/*****************************************/
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

/* Duyet theo chieu rong */
void breath_first_search(Graph* G, int k, int mark[]) {
Queue L;
make_null_queue(&L);
/* Kh?i t?o mark, chua d?nh nào du?c xét */
int j;
/* Ðua 1 vào frontier */
push_Q(&L, k);
/* Vòng l?p chính dùng d? duy?t */
while (!empty_Q(&L)) {
/* L?y ph?n t? d?u tiên trong L ra */
int x = top_Q(&L); pop_Q(&L);
if (mark[x] != 0) // Ðã duy?t r?i, b? qua
continue;
printf("Duyet %d\n", x);
mark[x] = 1; //Ðánh d?u nó dã duy?t
/* L?y các d?nh k? c?a nó */
List list = neighbors(G, x);
/* Xét các d?nh k? c?a nó */
for (j = 1; j <= list.size; j++) {
int y = element_at(&list, j);
push_Q(&L, y);
}
}
}

int main(){
	freopen("dothi.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
		
	int mark[MAX_VERTICES];
	int i;
	
	//rong
	for(i=1; i<=G.n; i++){
		mark[i] = 0;
	}
	
	for(i =1; i <= G.n; i++ ){
		if(mark[i] == 0){
			breath_first_search(&G,i, mark);
		}
	}
	
}
