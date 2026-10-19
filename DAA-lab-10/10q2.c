#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int *grid;
    int R;
    int C;
    int count;
} DSU;

DSU* create_dsu(int R, int C) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    int total = R * C;
    dsu->parent = (int*)malloc(total * sizeof(int));
    dsu->rank = (int*)calloc(total, sizeof(int));
    dsu->grid = (int*)calloc(total, sizeof(int));
    dsu->R = R;
    dsu->C = C;
    dsu->count = 0;

    for (int i = 0; i < total; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

int find_set(DSU *dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    return dsu->parent[i] = find_set(dsu, dsu->parent[i]);
}

void union_sets(DSU *dsu, int i, int j) {
    int root_i = find_set(dsu, i);
    int root_j = find_set(dsu, j);

    if (root_i != root_j) {
        if (dsu->rank[root_i] < dsu->rank[root_j]) {
            dsu->parent[root_i] = root_j;
        } else if (dsu->rank[root_i] > dsu->rank[root_j]) {
            dsu->parent[root_j] = root_i;
        } else {
            dsu->parent[root_j] = root_i;
            dsu->rank[root_i]++;
        }
        dsu->count--;
    }
}

int add_land(DSU *dsu, int r, int c) {
    int idx = r * dsu->C + c;

    if (dsu->grid[idx] == 1) {
        return dsu->count;
    }

    dsu->grid[idx] = 1;
    dsu->count++;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < dsu->R && nc >= 0 && nc < dsu->C) {
            int n_idx = nr * dsu->C + nc;
            if (dsu->grid[n_idx] == 1) {
                union_sets(dsu, idx, n_idx);
            }
        }
    }

    return dsu->count;
}

void free_dsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu->grid);
    free(dsu);
}

int main() {
    int R, C, K;
    if (scanf("%d %d %d", &R, &C, &K) != 3) return 0;

    DSU *dsu = create_dsu(R, C);

    for (int i = 0; i < K; i++) {
        int r, c;
        scanf("%d %d", &r, &c);
        int num_islands = add_land(dsu, r, c);
        printf("After adding land at (%d, %d): %d island(s)\n", r, c, num_islands);
    }

    free_dsu(dsu);
    return 0;
}