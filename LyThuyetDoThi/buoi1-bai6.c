#include "stdio.h"

#define MAX_VERTICES 100

typedef struct {
int n; /* n: so dinh */
/* ma tran dinh � dinh */
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
G->A[x][y] += 1; //y ke v?i x
G->A[y][x] += 1; //x ke voi y
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
return G->A[x][y] != 0;
}

///* Tinh bac cua dinh x: deg(x) */
//int degree(Graph* G, int x) {
//int y, deg = 0;
//for (y = 1; y <= G->n; y++)
//if (G->A[x][y] > 0)
//deg++;
//return deg;
//}

/* Tinh bac cua dinh x: deg(x), truong hop da cung */
int degree(Graph* G, int x) {
int y, deg = 0;
for (y = 1; y <= G->n; y++)
deg += G->A[x][y];
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
if (adjacent(G, x, y)){
	int i;
	for(i=1; i <= G->A[x][y]; i++){
		push_back(&list,y);
	}
}
return list;
}

/* Ham main() */
/* Ham main() */
int main() {
Graph G;
int y;
/* Bi?u di?n d? th? */
int n, m, e, u, v;
FILE* file = fopen("dothi2.txt", "r");
fscanf(file, "%d%d", &n, &m);
init_graph(&G, n);
for (e = 1; e <= m; e++) {
fscanf(file, "%d%d", &u, &v);
add_edge(&G, u, v);
}
/* Li?t k� danh s�ch k? c?a c�c d?nh */
for (v = 1; v <= n; v++) {
List list = neighbors(&G, v);
printf("Cac dinh ke cua %d: [", v);
for (y = 1; y <= list.size; y++)
printf("%d ", element_at(&list, y));
printf("]\n");
}

return 0;
}
