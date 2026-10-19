#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *size;
    long long *total_weight;
    int K;
    long long max_valid_weight;
} DSU;

DSU* create_dsu(int V, long long *vertex_weights, int K) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(V * sizeof(int));
    dsu->size = (int*)malloc(V * sizeof(int));
    dsu->total_weight = (long long*)malloc(V * sizeof(long long));
    dsu->K = K;
    dsu->max_valid_weight = 0;

    for (int i = 0; i < V; i++) {
        dsu->parent[i] = i;
        dsu->size[i] = 1;
        dsu->total_weight[i] = vertex_weights[i];

        if (1 <= K) {
            if (vertex_weights[i] > dsu->max_valid_weight) {
                dsu->max_valid_weight = vertex_weights[i];
            }
        }
    }
    return dsu;
}

int find_set(DSU *dsu, int v) {
    if (v == dsu->parent[v])
        return v;
    return dsu->parent[v] = find_set(dsu, dsu->parent[v]);
}

void add_edge(DSU *dsu, int u, int v) {
    int root_u = find_set(dsu, u);
    int root_v = find_set(dsu, v);

    if (root_u != root_v) {
        if (dsu->size[root_u] < dsu->size[root_v]) {
            int temp = root_u;
            root_u = root_v;
            root_v = temp;
        }

        dsu->parent[root_v] = root_u;
        dsu->size[root_u] += dsu->size[root_v];
        dsu->total_weight[root_u] += dsu->total_weight[root_v];

        if (dsu->size[root_u] <= dsu->K) {
            if (dsu->total_weight[root_u] > dsu->max_valid_weight) {
                dsu->max_valid_weight = dsu->total_weight[root_u];
            }
        }
    }
}

long long get_max_weight(DSU *dsu) {
    return dsu->max_valid_weight;
}

void free_dsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu->size);
    free(dsu->total_weight);
    free(dsu);
}

int main() {
    int V, E, K;
    if (scanf("%d %d %d", &V, &E, &K) != 3) return 0;

    long long *weights = (long long*)malloc(V * sizeof(long long));
    for (int i = 0; i < V; i++) {
        scanf("%lld", &weights[i]);
    }

    DSU *dsu = create_dsu(V, weights, K);
    free(weights);

    printf("Initial max weight (size <= %d): %lld\n", K, get_max_weight(dsu));

    for (int i = 0; i < E; i++) {
        int u, v;
        long long edge_w;
        scanf("%d %d %lld", &u, &v, &edge_w);

        add_edge(dsu, u, v);
        printf("After edge (%d, %d): Max component weight (size <= %d) = %lld\n",
               u, v, K, get_max_weight(dsu));
    }

    free_dsu(dsu);
    return 0;
}