#include <stdio.h>
#include <stdlib.h>

typedef struct EdgeNode {
    int to;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    EdgeNode **head;
} Graph;

Graph* create_graph(int V) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->head = (EdgeNode**)calloc(V, sizeof(EdgeNode*));
    return g;
}

void add_edge(Graph *g, int u, int v) {
    EdgeNode *node1 = (EdgeNode*)malloc(sizeof(EdgeNode));
    node1->to = v;
    node1->next = g->head[u];
    g->head[u] = node1;

    EdgeNode *node2 = (EdgeNode*)malloc(sizeof(EdgeNode));
    node2->to = u;
    node2->next = g->head[v];
    g->head[v] = node2;
}

typedef struct {
    int *parent;
    long long *sum;
    int *active;
    long long max_sum;
} DSU;

DSU* create_dsu(int V, long long *weights) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(V * sizeof(int));
    dsu->sum = (long long*)malloc(V * sizeof(long long));
    dsu->active = (int*)calloc(V, sizeof(int));
    dsu->max_sum = 0;

    for (int i = 0; i < V; i++) {
        dsu->parent[i] = i;
        dsu->sum[i] = weights[i];
    }
    return dsu;
}

int find_set(DSU *dsu, int v) {
    if (v == dsu->parent[v])
        return v;
    return dsu->parent[v] = find_set(dsu, dsu->parent[v]);
}

void activate_vertex(DSU *dsu, Graph *g, int u) {
    dsu->active[u] = 1;
    if (dsu->sum[u] > dsu->max_sum) {
        dsu->max_sum = dsu->sum[u];
    }

    EdgeNode *curr = g->head[u];
    while (curr != NULL) {
        int v = curr->to;
        if (dsu->active[v]) {
            int root_u = find_set(dsu, u);
            int root_v = find_set(dsu, v);

            if (root_u != root_v) {
                dsu->parent[root_v] = root_u;
                dsu->sum[root_u] += dsu->sum[root_v];
                if (dsu->sum[root_u] > dsu->max_sum) {
                    dsu->max_sum = dsu->sum[root_u];
                }
            }
        }
        curr = curr->next;
    }
}

void free_graph(Graph *g, int V) {
    for (int i = 0; i < V; i++) {
        EdgeNode *curr = g->head[i];
        while (curr != NULL) {
            EdgeNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->head);
    free(g);
}

void free_dsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu->sum);
    free(dsu->active);
    free(dsu);
}

int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 0;

    long long *weights = (long long*)malloc(V * sizeof(long long));
    for (int i = 0; i < V; i++) {
        scanf("%lld", &weights[i]);
    }

    Graph *g = create_graph(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(g, u, v);
    }

    int *P = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        scanf("%d", &P[i]);
    }

    DSU *dsu = create_dsu(V, weights);
    long long *ans = (long long*)malloc(V * sizeof(long long));

    for (int i = V - 1; i >= 0; i--) {
        ans[i] = dsu->max_sum;
        activate_vertex(dsu, g, P[i]);
    }

    for (int i = 0; i < V; i++) {
        printf("After deleting vertex %d: Maximum component sum = %lld\n", P[i], ans[i]);
    }

    free(weights);
    free(P);
    free(ans);
    free_dsu(dsu);
    free_graph(g, V);

    return 0;
}