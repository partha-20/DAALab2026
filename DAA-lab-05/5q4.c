#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter number of elements (N): ");
    scanf("%d", &n);

    // 1. Generate N random numbers and store in file
    FILE *fp = fopen("input_heap.txt", "w");
    srand(time(0));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", rand() % 1000);
    }
    fclose(fp);

    // 2. Read from file
    int *arr = (int*)malloc(n * sizeof(int));
    fp = fopen("input_heap.txt", "r");
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    // 3. Perform Heap Sort
    heapSort(arr, n);

    // 4. Save sorted data to output file
    fp = fopen("sorted_heapsort.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);

    printf("Heap Sort completed. Output saved to 'sorted_heapsort.txt'.\n");
    free(arr);
    return 0;
}
