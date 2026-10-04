#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void optimalBST(double p[], double q[], int n) {
    double** e = (double**)malloc((n + 2) * sizeof(double*));
    double** w = (double**)malloc((n + 2) * sizeof(double*));
    int** root = (int**)malloc((n + 1) * sizeof(int*));

    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double*)malloc((n + 1) * sizeof(double));
        w[i] = (double*)malloc((n + 1) * sizeof(double));
    }
    for (int i = 0; i <= n; i++) {
        root[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Minimum expected search cost: %.4f\n", e[1][n]);
    printf("Root of optimal tree: k%d\n\n", root[1][n]);

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
    }
    for (int i = 0; i <= n; i++) {
        free(root[i]);
    }
    free(e);
    free(w);
    free(root);
}

int main() {
    double p[] = {0.0, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    int n = 5;

    printf("Test Case (CLRS Example, 5 keys):\n");
    optimalBST(p, q, n);

    return 0;
}