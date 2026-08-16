#include <stdio.h>
#include <stdlib.h>
long long b_comps = 0, t_comps = 0;
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    b_comps = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        b_comps++;
        if (arr[mid] == key) return mid;
        b_comps++;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int ternarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    t_comps = 0;
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        t_comps++;
        if (arr[mid1] == key) return mid1;
        t_comps++;
        if (arr[mid2] == key) return mid2;
        t_comps++;
        if (key < arr[mid1]) high = mid1 - 1;
        else {
            t_comps++;
            if (key > arr[mid2]) low = mid2 + 1;
            else { low = mid1 + 1; high = mid2 - 1; }
        }
    }
    return -1;
}
int main() {
    FILE *fp = fopen("results1.csv", "w");
    if (!fp) return 1;
    fprintf(fp, "ArraySize,BinaryComparisons,TernaryComparisons\n");
    long sizes[] = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int test_arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int test_n = 10, key = 23;
    printf("Searching %d in array...\n", key);
    printf("Binary Search Index: %d (Comparisons: %lld)\n", binarySearch(test_arr, test_n, key), b_comps);
    printf("Ternary Search Index: %d (Comparisons: %lld)\n", ternarySearch(test_arr, test_n, key), t_comps);
    for (int i = 0; i < num_sizes; i++) {
        long n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        for (long j = 0; j < n; j++) arr[j] = j * 2;
        binarySearch(arr, n, -1);
        ternarySearch(arr, n, -1);
        fprintf(fp, "%ld,%lld,%lld\n", n, b_comps, t_comps);
        free(arr);
    }
    fclose(fp);
    return 0;
}
