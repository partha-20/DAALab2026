#include <stdio.h>
#include <stdlib.h>

int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);

    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    int** S1 = allocateMatrix(k);
    int** S2 = allocateMatrix(k);

    int** P1 = allocateMatrix(k);
    int** P2 = allocateMatrix(k);
    int** P3 = allocateMatrix(k);
    int** P4 = allocateMatrix(k);
    int** P5 = allocateMatrix(k);
    int** P6 = allocateMatrix(k);
    int** P7 = allocateMatrix(k);

    subtractMatrix(B12, B22, S1, k);
    strassen(A11, S1, P1, k);

    addMatrix(A11, A12, S1, k);
    strassen(S1, B22, P2, k);

    addMatrix(A21, A22, S1, k);
    strassen(S1, B11, P3, k);

    subtractMatrix(B21, B11, S1, k);
    strassen(A22, S1, P4, k);

    addMatrix(A11, A22, S1, k);
    addMatrix(B11, B22, S2, k);
    strassen(S1, S2, P5, k);

    subtractMatrix(A12, A22, S1, k);
    addMatrix(B21, B22, S2, k);
    strassen(S1, S2, P6, k);

    subtractMatrix(A21, A11, S1, k);
    addMatrix(B11, B12, S2, k);
    strassen(S1, S2, P7, k);

    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);

    addMatrix(P5, P4, S1, k);
    subtractMatrix(S1, P2, S2, k);
    addMatrix(S2, P6, C11, k);

    addMatrix(P1, P2, C12, k);

    addMatrix(P3, P4, C21, k);

    addMatrix(P1, P5, S1, k);
    subtractMatrix(S1, P3, S2, k);
    addMatrix(S2, P7, C22, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k); freeMatrix(A12, k); freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k); freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(P1, k); freeMatrix(P2, k); freeMatrix(P3, k); freeMatrix(P4, k);
    freeMatrix(P5, k); freeMatrix(P6, k); freeMatrix(P7, k);
    freeMatrix(S1, k); freeMatrix(S2, k);
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        printf("[ ");
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("]\n");
    }
}

int main() {
    int n = 4;

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    int valA = 1, valB = 16;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = valA++;
            B[i][j] = valB--;
        }
    }

    printf("Matrix A:\n");
    printMatrix(A, n);

    printf("\nMatrix B:\n");
    printMatrix(B, n);

    strassen(A, B, C, n);

    printf("\nResult Matrix C (A x B):\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
