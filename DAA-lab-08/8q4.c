#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* tails, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tails[mid] >= target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int lengthOfLIS(int* A, int n) {
    if (n == 0) return 0;

    int* tails = (int*)malloc(n * sizeof(int));
    if (tails == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    int length = 0;

    for (int i = 0; i < n; i++) {
        int idx = binarySearch(tails, 0, length - 1, A[i]);
        tails[idx] = A[i];
        if (idx == length) {
            length++;
        }
    }

    free(tails);
    return length;
}

int main() {
    int A1[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n1 = sizeof(A1) / sizeof(A1[0]);
    printf("Test Case 1:\n");
    printf("Array: {10, 9, 2, 5, 3, 7, 101, 18}\n");
    printf("Expected LIS Length: 4 ({2, 3, 7, 101} or {2, 5, 7, 101})\n");
    printf("Actual LIS Length: %d\n\n", lengthOfLIS(A1, n1));

    int A2[] = {0, 1, 0, 3, 2, 3};
    int n2 = sizeof(A2) / sizeof(A2[0]);
    printf("Test Case 2:\n");
    printf("Array: {0, 1, 0, 3, 2, 3}\n");
    printf("Expected LIS Length: 4 ({0, 1, 2, 3})\n");
    printf("Actual LIS Length: %d\n\n", lengthOfLIS(A2, n2));

    int A3[] = {7, 7, 7, 7, 7};
    int n3 = sizeof(A3) / sizeof(A3[0]);
    printf("Test Case 3:\n");
    printf("Array: {7, 7, 7, 7, 7}\n");
    printf("Expected LIS Length: 1\n");
    printf("Actual LIS Length: %d\n", lengthOfLIS(A3, n3));

    return 0;
}