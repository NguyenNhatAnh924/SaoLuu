#include "stdio.h"
typedef struct {
	int u, v; // dinh dau u, dinh cuoi v
	int w; 		// trong so
} Edge;

typedef struct {
	int n, m; 	// n dinh m cung
	Edge edges[100]; // luu cung
} Graph;

void add_edge(Graph* G, int u, int v, int w) {
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
}

void init_graph(Graph* G, int n) {
	G->n = n;
	G->m = 0;
}

void read_File(Graph* G, int* s){
	freopen("dothi3.txt" , "r", stdin);
	int n,m;
	scanf("%d %d", &n , &m);
	init_graph(G, n);
	int i;
	for(i = 0; i < m; i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		add_edge(G,u,v,w);
	}
	scanf("%d",s);
}

#define INFINITY 999
#define MAXN 100
int pi[MAXN];
int p[MAXN];
int BellmanFord(Graph* G, int s) {
	int i, it,k;
	for (i = 1; i <= G->n; i++) {
		pi[i] = INFINITY;
	}
	
	pi[s] = 0;
	p[s] = -1; //tru?c d?nh s không có d?nh nào c?
	// l?p n ho?c n-1 l?n d?u du?c
	for (it = 1; it < G->n; it++) {
	// Duy?t qua các cung và c?p nh?t (n?u tho?)
		for (k = 0; k < G->m; k++) {
			int u = G->edges[k].u;
			int v = G->edges[k].v;
			int w = G->edges[k].w;
			if (pi[u] + w < pi[v]) {
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	
	for(it=0; it < G->m ; it++){
		Edge e = G->edges[it];
		if(pi[e.u] != INFINITY && pi[e.u] + e.w < pi[e.v]){
			return 1;
		}
	}
	return 0;
}
 int main(){
 	int s=1;
 	Graph G;
 	read_File(&G,&s);
 	BellmanFord(&G,1);
 	int i;
	for (i = 1; i <= G.n; i++)
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
 	return 0;
 }
