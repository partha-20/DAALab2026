#include <stdio.h>
#include <stdlib.h>

int maxSumIS(int* A, int n) {
    if (n == 0) return 0;

    int* msis = (int*)malloc(n * sizeof(int));
    if (msis == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    int max_sum = 0;

    for (int i = 0; i < n; i++) {
        msis[i] = A[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j] && msis[i] < msis[j] + A[i]) {
                msis[i] = msis[j] + A[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (msis[i] > max_sum) {
            max_sum = msis[i];
        }
    }

    free(msis);
    return max_sum;
}

int main() {
    int A1[] = {1, 101, 2, 3, 100, 4, 5};
    int n1 = sizeof(A1) / sizeof(A1[0]);
    printf("Test Case 1:\n");
    printf("Array: {1, 101, 2, 3, 100, 4, 5}\n");
    printf("Expected Max Sum: 106 ({1, 2, 3, 100})\n");
    printf("Actual Max Sum: %d\n\n", maxSumIS(A1, n1));

    int A2[] = {3, 4, 5, 10};
    int n2 = sizeof(A2) / sizeof(A2[0]);
    printf("Test Case 2:\n");
    printf("Array: {3, 4, 5, 10}\n");
    printf("Expected Max Sum: 22 ({3, 4, 5, 10})\n");
    printf("Actual Max Sum: %d\n\n", maxSumIS(A2, n2));

    int A3[] = {10, 5, 4, 3};
    int n3 = sizeof(A3) / sizeof(A3[0]);
    printf("Test Case 3:\n");
    printf("Array: {10, 5, 4, 3}\n");
    printf("Expected Max Sum: 10 ({10})\n");
    printf("Actual Max Sum: %d\n", maxSumIS(A3, n3));

    return 0;
}