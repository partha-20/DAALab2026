#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
} DSU;

DSU* create_dsu(int n) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

int find_set(DSU *dsu, int v) {
    if (v == dsu->parent[v])
        return v;
    return dsu->parent[v] = find_set(dsu, dsu->parent[v]);
}

void union_sets(DSU *dsu, int u, int v) {
    int root_u = find_set(dsu, u);
    int root_v = find_set(dsu, v);

    if (root_u != root_v) {
        if (dsu->rank[root_u] < dsu->rank[root_v]) {
            dsu->parent[root_u] = root_v;
        } else if (dsu->rank[root_u] > dsu->rank[root_v]) {
            dsu->parent[root_v] = root_u;
        } else {
            dsu->parent[root_v] = root_u;
            dsu->rank[root_u]++;
        }
    }
}

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void free_dsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    int *A = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    DSU *dsu = create_dsu(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(dsu, u, v);
    }

    int *comp_size = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        int root = find_set(dsu, i);
        comp_size[root]++;
    }

    int **comp_indices = (int**)malloc(N * sizeof(int*));
    int **comp_values = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        if (comp_size[i] > 0) {
            comp_indices[i] = (int*)malloc(comp_size[i] * sizeof(int));
            comp_values[i] = (int*)malloc(comp_size[i] * sizeof(int));
        } else {
            comp_indices[i] = NULL;
            comp_values[i] = NULL;
        }
    }

    int *comp_ptr = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        int root = find_set(dsu, i);
        int pos = comp_ptr[root]++;
        comp_indices[root][pos] = i;
        comp_values[root][pos] = A[i];
    }

    for (int i = 0; i < N; i++) {
        if (comp_size[i] > 0) {
            qsort(comp_values[i], comp_size[i], sizeof(int), compare_ints);
            qsort(comp_indices[i], comp_size[i], sizeof(int), compare_ints);

            for (int k = 0; k < comp_size[i]; k++) {
                A[comp_indices[i][k]] = comp_values[i][k];
            }
        }
    }

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        if (comp_size[i] > 0) {
            free(comp_indices[i]);
            free(comp_values[i]);
        }
    }
    free(comp_indices);
    free(comp_values);
    free(comp_size);
    free(comp_ptr);
    free(A);
    free_dsu(dsu);

    return 0;
}