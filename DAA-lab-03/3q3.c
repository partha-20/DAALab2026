#include <stdio.h>

int comparisons = 0;

typedef struct {
    int min;
    int max;
} Pair;

Pair getMinMax(int arr[], int low, int high) {
    Pair result, left, right;

    // Base Case 1: Single element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }
    // Base Case 2: Two elements
    if (high == low + 1) {
        comparisons++;
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }
    // Divide
    int mid = low + (high - low) / 2;
    left = getMinMax(arr, low, mid);
    right = getMinMax(arr, mid + 1, high);

    // Combine (2 comparisons)
    comparisons++;
    result.min = (left.min < right.min) ? left.min : right.min;

    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

void printArray(int arr[], int n) {
    printf("Array Elements: [ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main() {
    int arr[] = {1000, 11, 445, 1, 330, 3000, 89, 15, 72, 500};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf(" MIN AND MAX FINDER USING DIVIDE AND CONQUER \n");
    printArray(arr, n);
    printf("Array Size (n): %d\n", n);
    comparisons = 0;
    Pair minmax = getMinMax(arr, 0, n - 1);
    printf("RESULTS:\n");
    printf("  Minimum Element : %d\n", minmax.min);
    printf("  Maximum Element : %d\n", minmax.max);
    printf("COMPARISON ANALYSIS:\n");
    printf("  Actual Comparisons Made  : %d\n", comparisons);
    printf("  Theoretical Upper Bound  : %d  (3n/2 = %d)\n", (3 * n) / 2 - 2, (3 * n) / 2);
    printf("  Naive Linear Search Cost : %d  (2n - 2)\n", 2 * n - 2);
    return 0;
}
