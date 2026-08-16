#include <stdio.h>

long long total_comparisons = 0;

void selectionSort(int A[], int n) {
    total_comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            total_comparisons++;
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        int temp = A[i];
        A[i] = A[min_idx];
        A[min_idx] = temp;
    }
}

void printArray(int A[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("]\n");
}

int main() {
    int worst_case[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int best_case[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = 9;

    printf("===========================================\n");
    printf(" SELECTION SORT LOOP INVARIANT VALIDATION \n");
    printf("===========================================\n\n");

    printf("--- Worst-Case Test (Reverse Sorted) ---\n");
    printf("Original: ");
    printArray(worst_case, n);
    selectionSort(worst_case, n);
    printf("Sorted  : ");
    printArray(worst_case, n);
    printf("Comparisons Made: %lld\n\n", total_comparisons);

    printf("--- Best-Case Test (Already Sorted) ---\n");
    printf("Original: ");
    printArray(best_case, n);
    selectionSort(best_case, n);
    printf("Sorted  : ");
    printArray(best_case, n);
    printf("Comparisons Made: %lld\n\n", total_comparisons);

    printf("Expected Formula Value (n*(n-1)/2): %d\n", n * (n - 1) / 2);
    printf("===========================================\n");

    return 0;
}
