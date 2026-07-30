#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10};
    int arr2[] = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10};
    int n = 10;
    int comp_optimized = 0, comp_standard = 0;
    int i, j, swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            comp_optimized++;
            if (arr1[j] > arr1[j + 1]) {
                swap(&arr1[j], &arr1[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comp_standard++;
            if (arr2[j] > arr2[j + 1]) {
                swap(&arr2[j], &arr2[j + 1]);
            }
        }
    }

    printf("Optimized Comparisons: %d\n", comp_optimized);
    printf("Standard Comparisons: %d\n", comp_standard);

    return 0;
}