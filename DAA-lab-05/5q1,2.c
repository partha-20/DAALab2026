#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int index = partition(arr, low, high);

        if (index - low == k - 1)
            return arr[index];

        if (index - low > k - 1)
            return quickSelect(arr, low, index - 1, k);

        return quickSelect(arr, index + 1, high, k - (index - low + 1));
    }
    return -1;
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int kthSmallest = quickSelect(arr, 0, n - 1, k);
    printf("The %d-th smallest element is: %d\n", k, kthSmallest);

    int median = quickSelect(arr, 0, n - 1, (n + 1) / 2);
    printf("The median element is: %d\n", median);

    return 0;
}
