#include <stdio.h>
#include <stdlib.h>

int** allocMat(int n) {
    int** M = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        M[i] = (int*)calloc(n, sizeof(int));
    }
    return M;
}

void freeMat(int n, int** M) {
    for(int i = 0; i < n; i++) free(M[i]);
    free(M);
}

void multiplyStructured(int n, int** A, int** B, int** C) {
    if(n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int** A1 = allocMat(k);
    int** A2 = allocMat(k);
    int** B1 = allocMat(k);
    int** B2 = allocMat(k);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    int** sumA  = allocMat(k);
    int** diffA = allocMat(k);
    int** sumB  = allocMat(k);
    int** diffB = allocMat(k);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            sumA[i][j]  = A1[i][j] + A2[i][j];
            diffA[i][j] = A1[i][j] - A2[i][j];
            sumB[i][j]  = B1[i][j] + B2[i][j];
            diffB[i][j] = B1[i][j] - B2[i][j];
        }
    }

    int** P1 = allocMat(k);
    int** P2 = allocMat(k);

    multiplyStructured(k, sumA, sumB, P1);
    multiplyStructured(k, diffA, diffB, P2);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            int c1 = (P1[i][j] + P2[i][j]) / 2;
            int c2 = (P1[i][j] - P2[i][j]) / 2;

            C[i][j]         = c1;
            C[i + k][j + k] = c1;
            C[i][j + k]     = c2;
            C[i + k][j]     = c2;
        }
    }

    freeMat(k, A1); freeMat(k, A2);
    freeMat(k, B1); freeMat(k, B2);
    freeMat(k, sumA); freeMat(k, diffA);
    freeMat(k, sumB); freeMat(k, diffB);
    freeMat(k, P1); freeMat(k, P2);
}

void printMatrix(int n, int** M) {
    for(int i = 0; i < n; i++) {
        printf("[ ");
        for(int j = 0; j < n; j++) {
            printf("%4d ", M[i][j]);
        }
        printf("]\n");
    }
}

int main() {
    int n = 4;

    int** A = allocMat(n);
    int** B = allocMat(n);
    int** C = allocMat(n);

    int valA1[2][2] = {{1, 2}, {2, 1}};
    int valA2[2][2] = {{3, 4}, {4, 3}};

    int valB1[2][2] = {{5, 6}, {6, 5}};
    int valB2[2][2] = {{7, 8}, {8, 7}};

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            A[i][j]         = valA1[i][j];
            A[i + 2][j + 2] = valA1[i][j];
            A[i][j + 2]     = valA2[i][j];
            A[i + 2][j]     = valA2[i][j];

            B[i][j]         = valB1[i][j];
            B[i + 2][j + 2] = valB1[i][j];
            B[i][j + 2]     = valB2[i][j];
            B[i + 2][j]     = valB2[i][j];
        }
    }

    printf("Matrix A:\n");
    printMatrix(n, A);

    printf("\nMatrix B:\n");
    printMatrix(n, B);

    multiplyStructured(n, A, B, C);

    printf("\nMatrix C (A * B):\n");
    printMatrix(n, C);

    freeMat(n, A);
    freeMat(n, B);
    freeMat(n, C);

    return 0;
}
