#include "stdio.h"

#define MAXN 100
#define NO_EDGE 0

#define INFINITY 999
int mark[MAXN];
int pi[MAXN];
int p[MAXN];

//hoac gia tri dac biet nao do
typedef struct {
int n;
int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* G, int n) {
G->n = n;
int i, j;
	for (i = 1; i <= n; i++){
		for (j = 1; j <= n; j++){
			G->L[i][j] = NO_EDGE;
		}	
	}
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y, int w) {
	G->L[x][y] = w;
}

Graph read_File(){
	freopen("dothi3.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	return G;
}

void Dijkstra(Graph* G, int s) {
	int i, j, it;
	for (i = 1; i <= G->n; i++) {
		pi[i] = INFINITY;
		mark[i] = 0;
	}
	pi[s] = 0;
	p[s] = -1; //tru?c d?nh s không có d?nh nào c?
	// l?p n ho?c n-1 l?n d?u du?c
	for (it = 1; it < G->n; it++) {
	//1. Tìm i có mark[i] == 0 va có pi[i] nh? nh?t
		int min_pi = INFINITY;
		for (j = 1; j <= G->n; j++)
		if (mark[j] == 0 && pi[j] < min_pi) {
		min_pi = pi[j];
		i = j;
	}
	//Ðánh d?u i dã xét
	mark[i] = 1;
	//2. C?p nh?t pi và p c?a các d?nh k? c?a i (n?u tho?)
	for (j = 1; j <= G->n; j++)
		if (G->L[i][j] != NO_EDGE && mark[j] == 0) {
			if (pi[i] + G->L[i][j] < pi[j]) {
				pi[j] = pi[i] + G->L[i][j];	
				p[j] = i;
			}
		}
	}
}


int main() {
    Graph G;
    G = read_File();
    int i;
    int start_vertex = 1; 
    Dijkstra(&G, start_vertex);
//	if(pi[G.n] == INFINITY){
//		printf("-1");
//	}else{
//		printf("%d",pi[G.n]);
//	}
	for (i = 1; i <= G.n; i++)
	printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    
    return 0;
}


