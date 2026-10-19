#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int parent;
    int rank;
    int parity;
} DSU;

DSU* create_dsu(int v) {
    DSU *dsu = (DSU*)malloc(v * sizeof(DSU));
    for (int i = 0; i < v; i++) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
        dsu[i].parity = 0;
    }
    return dsu;
}

int find_set(DSU *dsu, int v, int *parity) {
    if (v == dsu[v].parent) {
        *parity = 0;
        return v;
    }
    int p_parity = 0;
    int root = find_set(dsu, dsu[v].parent, &p_parity);
    dsu[v].parent = root;
    dsu[v].parity ^= p_parity;
    *parity = dsu[v].parity;
    return root;
}

int add_edge(DSU *dsu, int u, int v) {
    int parity_u = 0, parity_v = 0;
    int root_u = find_set(dsu, u, &parity_u);
    int root_v = find_set(dsu, v, &parity_v);

    if (root_u == root_v) {
        if (parity_u == parity_v) {
            return 0;
        }
        return 1;
    }

    if (dsu[root_u].rank < dsu[root_v].rank) {
        int temp = root_u;
        root_u = root_v;
        root_v = temp;
    }

    dsu[root_v].parent = root_u;
    dsu[root_v].parity = parity_u ^ parity_v ^ 1;

    if (dsu[root_u].rank == dsu[root_v].rank) {
        dsu[root_u].rank++;
    }

    return 1;
}

int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 0;

    DSU *dsu = create_dsu(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (add_edge(dsu, u, v)) {
            printf("Edge (%d, %d): Added (Graph remains bipartite)\n", u, v);
        } else {
            printf("Edge (%d, %d): Skipped (Violates bipartiteness / Creates odd cycle)\n", u, v);
        }
    }

    free(dsu);
    return 0;
}