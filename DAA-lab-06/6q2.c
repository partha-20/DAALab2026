#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Dynamic allocation helper for 1D contiguous block representing 2D matrix
double* createMatrix(int n) {
    return (double*)calloc(n * n, sizeof(double));
}

// Memory index helper: A[i][j] -> A[i * n + j]
#define MAT(A, i, j, n) ((A)[(i) * (n) + (j)])

// Utility to print a matrix
void printMatrix(const double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", MAT(A, i, j, n));
        }
        printf("\n");
    }
}

// (i) Matrix Addition - O(n^2)
double* matrixAdd(const double *A, const double *B, int n) {
    double *C = createMatrix(n);
    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

// (ii) Matrix Multiplication - O(n^3)
double* matrixMultiply(const double *A, const double *B, int n) {
    double *C = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                MAT(C, i, j, n) += MAT(A, i, k, n) * MAT(B, k, j, n);
            }
        }
    }
    return C;
}

// (iii) Is Zero Matrix - O(n^2)
int isZeroMatrix(const double *A, int n) {
    for (int i = 0; i < n * n; i++) {
        if (fabs(A[i]) > 1e-9) return 0;
    }
    return 1;
}

// (iv) Is Symmetric Matrix - O(n^2)
int isSymmetric(const double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(MAT(A, i, j, n) - MAT(A, j, i, n)) > 1e-9) return 0;
        }
    }
    return 1;
}

// (v) Determinant using Gaussian Elimination - O(n^3)
double computeDeterminant(const double *A, int n) {
    double *temp = createMatrix(n);
    for (int i = 0; i < n * n; i++) temp[i] = A[i];

    double det = 1.0;
    int swaps = 0;

    for (int i = 0; i < n; i++) {
        // Pivot searching
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(MAT(temp, k, i, n)) > fabs(MAT(temp, pivot, i, n))) {
                pivot = k;
            }
        }

        if (fabs(MAT(temp, pivot, i, n)) < 1e-9) {
            free(temp);
            return 0.0; // Singular matrix
        }

        if (pivot != i) {
            for (int j = 0; j < n; j++) {
                double t = MAT(temp, i, j, n);
                MAT(temp, i, j, n) = MAT(temp, pivot, j, n);
                MAT(temp, pivot, j, n) = t;
            }
            swaps++;
        }

        det *= MAT(temp, i, i, n);

        for (int k = i + 1; k < n; k++) {
            double factor = MAT(temp, k, i, n) / MAT(temp, i, i, n);
            for (int j = i + 1; j < n; j++) {
                MAT(temp, k, j, n) -= factor * MAT(temp, i, j, n);
            }
        }
    }

    if (swaps % 2 != 0) det = -det;
    free(temp);
    return det;
}

// (vi) In-Situ Transpose - O(n^2) time, O(1) space
void transposeInPlace(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = MAT(A, i, j, n);
            MAT(A, i, j, n) = MAT(A, j, i, n);
            MAT(A, j, i, n) = temp;
        }
    }
}

// (vii) Dominant Eigenvalue and Eigenvector via Power Iteration Method
// Time: O(k * n^2) where k is iterations to convergence
double powerIteration(const double *A, double *eigenvector, int n, int maxIter) {
    for (int i = 0; i < n; i++) eigenvector[i] = 1.0; // Initial guess

    double eigenvalue = 0.0;
    double *nextVec = (double*)calloc(n, sizeof(double));

    for (int iter = 0; iter < maxIter; iter++) {
        // Matrix-Vector product: nextVec = A * eigenvector
        for (int i = 0; i < n; i++) {
            nextVec[i] = 0.0;
            for (int j = 0; j < n; j++) {
                nextVec[i] += MAT(A, i, j, n) * eigenvector[j];
            }
        }

        // Find max element for normalization (Rayleigh Quotient proxy)
        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(nextVec[i]) > fabs(norm)) norm = nextVec[i];
        }

        if (fabs(norm) < 1e-9) break;

        for (int i = 0; i < n; i++) {
            eigenvector[i] = nextVec[i] / norm;
        }

        eigenvalue = norm;
    }

    free(nextVec);
    return eigenvalue;
}

int main() {
    int n = 3;
    double *A = createMatrix(n);
    double *B = createMatrix(n);

    // Initialize sample matrices
    double valA[9] = {2, -1, 0, -1, 2, -1, 0, -1, 2};
    double valB[9] = {1,  2, 3,  2, 4,  5, 3,  5, 6};
    for(int i = 0; i < n * n; i++) {
        A[i] = valA[i];
        B[i] = valB[i];
    }

    printf("Matrix A (3x3 Symmetric Positive Definite):\n");
    printMatrix(A, n);

    printf("\n--- Validation & Results ---\n");

    // (i) Addition
    double *C_add = matrixAdd(A, B, n);
    printf("(i) Matrix Addition (A + B):\n");
    printMatrix(C_add, n);
    free(C_add);

    // (ii) Multiplication
    double *C_mul = matrixMultiply(A, B, n);
    printf("\n(ii) Matrix Multiplication (A * B):\n");
    printMatrix(C_mul, n);
    free(C_mul);

    // (iii) Zero Matrix check
    printf("\n(iii) Is A a Zero Matrix? %s\n", isZeroMatrix(A, n) ? "Yes" : "No");

    // (iv) Symmetric check
    printf("(iv)  Is A Symmetric? %s\n", isSymmetric(A, n) ? "Yes" : "No");

    // (v) Determinant
    printf("(v)   Determinant of A: %.2f\n", computeDeterminant(A, n));

    // (vi) In-Situ Transpose
    double *A_copy = createMatrix(n);
    for(int i = 0; i < n*n; i++) A_copy[i] = A[i];
    transposeInPlace(A_copy, n);
    printf("(vi)  In-Situ Transposed A:\n");
    printMatrix(A_copy, n);
    free(A_copy);

    // (vii) Eigenvalue & Eigenvector
    double *eigenVec = (double*)malloc(n * sizeof(double));
    double eigenVal = powerIteration(A, eigenVec, n, 100);
    printf("\n(vii) Dominant Eigenvalue of A: %.4f\n", eigenVal);
    printf("      Corresponding Eigenvector: [ ");
    for(int i = 0; i < n; i++) printf("%.4f ", eigenVec[i]);
    printf("]\n");

    free(eigenVec);
    free(A);
    free(B);
    return 0;
}
