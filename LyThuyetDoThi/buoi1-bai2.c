#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_ELEMENTS 100

// C?u tr�c d? th?
typedef struct {
    int n; // S? d?nh
    int A[MAX_VERTICES][MAX_VERTICES]; // Ma tr?n k?
} Graph;

// C?u tr�c danh s�ch
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;

// C?u tr�c ngan x?p
typedef struct {
    int data[MAX_ELEMENTS];
    int size;
} Stack;

// C?u tr�c h�ng d?i
typedef struct {
    int data[MAX_ELEMENTS];
    int front, rear;
} Queue;

// Bi?n to�n c?c
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];

// H�m kh?i t?o d? th?
void init_graph(Graph* G, int n) {
    G->n = n;
    int i,j;
    for ( i = 1; i <= n; i++)
        for ( j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

// H�m th�m c?nh v�o d? th?
void add_edge(Graph* G, int x, int y) {
    G->A[x][y] = 1; // y k? v?i x
    G->A[y][x] = 1; // x k? v?i y
}

// Ki?m tra xem y c� k? v?i x kh�ng
int adjacent(Graph* G, int x, int y) {
    return G->A[x][y] != 0;
}

// T�nh b?c c?a d?nh x
int degree(Graph* G, int x) {
    int deg = 0;
    int y;
    for ( y = 1; y <= G->n; y++)
        if (G->A[x][y] > 0)
            deg++;
    return deg;
}

// H�m kh?i t?o danh s�ch
void make_null(List* L) {
    L->size = 0;
}

// Th�m ph?n t? v�o cu?i danh s�ch
void push_back(List* L, ElementType x) {
    L->data[L->size++] = x;
}

// L?y ph?n t? t?i v? tr� i
ElementType element_at(List* L, int i) {
    return L->data[i - 1];
}

// S?p x?p danh s�ch
void sort(List* L) {
	int i,j;
    for ( i = 0; i < L->size - 1; i++) {
        for ( j = i + 1; j < L->size; j++) {
            if (L->data[i] > L->data[j]) {
                int tmp = L->data[i];
                L->data[i] = L->data[j];
                L->data[j] = tmp;
            }
        }
    }
}

// T�m c�c d?nh k? c?a d?nh x
List neighbors(Graph* G, int x) {
    List list;
    make_null(&list);
    int y;
    for ( y = 1; y <= G->n; y++)
        if (adjacent(G, x, y))
            push_back(&list, y);
    return list;
}

// H�m kh?i t?o ngan x?p
void make_null_stack(Stack* S) {
    S->size = 0;
}

// Th�m ph?n t? v�o ngan x?p
void push(Stack* S, int x) {
    S->data[S->size++] = x;
}

// L?y ph?n t? tr�n c�ng c?a ngan x?p
int top(Stack* S) {
    return S->data[S->size - 1];
}

// L?y ra ph?n t? tr�n c�ng c?a ngan x?p
void pop(Stack* S) {
    S->size--;
}

// Ki?m tra xem ngan x?p c� r?ng kh�ng
int empty(Stack* S) {
    return S->size == 0;
}

// Duy?t d? th? theo chi?u s�u
void depth_first_search(Graph* G, int k) {
    Stack L;
    make_null_stack(&L);
    push(&L, k);
    int j;
    while (!empty(&L)) {
        int x = top(&L); 
        pop(&L);
        if (mark[x] != 0) continue; // �� duy?t r?i
        printf("%d\n", x);
        mark[x] = 1; // ��nh d?u d� duy?t
        List list = neighbors(G, x);
        for ( j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            push(&L, y);
        }
    }
}

void depth_first_search_tree(Graph* G, int k) {
    Stack L;
    make_null_stack(&L);
    push(&L, k);
    int j;
    while (!empty(&L)) {
        int x = top(&L); 
        pop(&L);
        if (mark[x] != 0) continue; // �� duy?t r?i
        mark[x] = 1; // ��nh d?u d� duy?t
        List list = neighbors(G, x);
        for ( j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            if(y!=1 && parent[y]== -1){
			}
            push(&L, y);
        }
    }
}

// H�m kh?i t?o h�ng d?i
void make_null_queue(Queue* Q) {
    Q->front = 0;
    Q->rear = -1;
}

// Th�m ph?n t? v�o h�ng d?i
void push_Q(Queue* Q, int x) {
    Q->data[++Q->rear] = x;
}

// L?y ph?n t? d?u h�ng d?i
int top_Q(Queue* Q) {
    return Q->data[Q->front];
}

// L?y ra ph?n t? d?u h�ng d?i
void pop_Q(Queue* Q) {
    Q->front++;
}

// Ki?m tra xem h�ng d?i c� r?ng kh�ng
int empty_Q(Queue* Q) {
    return Q->front > Q->rear;
}

// Duy?t theo chi?u r?ng
void breath_first_search_tree(Graph* G, int k) {
    Queue L;
    make_null_queue(&L);
    parent[k] = 0;
    push_Q(&L, k);
    int j;
    while (!empty_Q(&L)) {
        int x = top_Q(&L); 
        pop_Q(&L);
        if (mark[x] != 0) continue; // �� duy?t r?i
        mark[x] = 1;
        List list = neighbors(G, x);
        for ( j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            if (y != 1 && parent[y] == -1) {
                parent[y] = x;
                push_Q(&L, y);
            }
        }
    }
}

// H�m main
int main() {
    freopen("dothi.txt", "r", stdin); // �?c t? t?p
    Graph G;
    int i,e,n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for ( e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for ( i = 1; i <= G.n; i++) {
        mark[i] = 0;
        parent[i] = -1;
    }

    for ( i = 1; i <= G.n; i++) {
        if (mark[i] == 0) {
           depth_first_search()
        }
    }

    for ( i = 1; i <= G.n; i++) {
        printf("%d %d\n", i, parent[i]);
    }

    return 0;
}

