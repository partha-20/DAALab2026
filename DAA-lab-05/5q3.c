#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of elements (N): ");
    scanf("%d", &n);

    // 1. Generate N random numbers and write to file
    FILE *fp = fopen("input.txt", "w");
    srand(time(0));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", rand() % 1000);
    }
    fclose(fp);

    // 2. Read elements from file
    int *arr = (int*)malloc(n * sizeof(int));
    fp = fopen("input.txt", "r");
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    // 3. Perform Quick Sort
    quickSort(arr, 0, n - 1);

    // 4. Save sorted output
    fp = fopen("sorted_quicksort.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);

    printf("Quick Sort completed successfully. Output saved to 'sorted_quicksort.txt'.\n");
    free(arr);
    return 0;
}
