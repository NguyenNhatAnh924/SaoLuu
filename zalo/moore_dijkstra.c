#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
#define NO_EDGE 0
#define INFINITY 9999999

typedef struct {
    int n;
    int L[MAXN][MAXN];
}Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    int i,j;
    for ( i = 1; i <= n; i++) {
        for ( j = 1; j <= n; j++) {
            G->L[i][j] = NO_EDGE; // Khởi tạo không có cạnh
        }
    }
}

void add_edge(Graph* G, int w, int u, int v) {
    G->L[u][v] = w; // Thêm cạnh từ u đến v với trọng số w
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void Dijkstra(Graph* G, int s) {
	int i,it,j;
    for ( i = 1; i <= G->n; i++) {
        pi[i] = INFINITY; // Khởi tạo tất cả khoảng cách là vô cực
        mark[i] = 0; // Đánh dấu chưa xét
    }
    pi[s] = 0; // Đặt khoảng cách từ s đến s là 0
    p[s] = -1; // Đỉnh trước s không có

    for ( it = 1; it < G->n; it++) {
        int min_pi = INFINITY;
        int i = -1; // Khởi tạo i với -1

        for ( j = 1; j <= G->n; j++) {
            if (mark[j] == 0 && pi[j] < min_pi) {
                min_pi = pi[j];
                i = j; // Cập nhật đỉnh có khoảng cách nhỏ nhất
            }
        }

        if (i == -1) break; // Nếu không còn đỉnh nào chưa xét

        mark[i] = 1; // Đánh dấu i đã xét

        for ( j = 1; j <= G->n; j++) {
            if (G->L[i][j] != NO_EDGE && mark[j] == 0) {
                if (pi[i] + G->L[i][j] < pi[j]) {
                    pi[j] = pi[i] + G->L[i][j]; // Cập nhật khoảng cách
                    p[j] = i; // Cập nhật đỉnh trước
                }
            }
        }
    }
}

int main() {
    Graph G;
    FILE* file = fopen("dothi.txt", "r");
    int  n, m;
	fscanf(file,"%d%d", &n, &m);
    printf("So dinh: %d, So canh: %d\n", n, m); // Thêm thông báo kiểm tra
    int i;
    init_graph(&G, n);
    for ( i = 0; i < m; i++) {
        int u, v, w;
      fscanf(file, "%d%d%d", &u, &v, &w) ;
            
        printf("Them canh tu %d den %d trong so %d\n", u, v, w); // Thông báo thêm cạnh
        add_edge(&G, w, u, v);
    }

    fclose(file); // Đóng tệp tin sau khi đọc

    Dijkstra(&G, 1); // Tìm đường đi ngắn nhất từ đỉnh 1

    // In ra kết quả
    for ( i = 1; i <= G.n; i++) {
        if (pi[i] == INFINITY) {
            printf("dinh %d khong the đen đuoc.\n", i);
        } else {
            printf("Khoang cach tu 1 den %d: %d, dinh truoc: %d\n", i, pi[i], p[i]);
        }
    }
    int path[MAXN]; // lưu các đỉnh trên đường đi
int k = 0; // số đỉnh của đường đi

int current = 7;
while (current != -1) {
path[k] = current; k++;
current = p[current];
}

for (i = k-1; i >=0; i--)
printf("%d", path[i]);
    
}
