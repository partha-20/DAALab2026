#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZES 6
int SIZES[NUM_SIZES] = {20000, 40000, 60000, 80000, 100000, 120000};

double get_time_us(clock_t start, clock_t end) {
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0;
}

// Standard 2-Way Merge Sort

void merge2(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort2(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort2(arr, l, m);
        mergeSort2(arr, m + 1, r);
        merge2(arr, l, m, r);
    }
}

// Modified 3-Way Merge Sort

void merge3(int arr[], int l, int m1, int m2, int r) {
    int n1 = m1 - l + 1;
    int n2 = m2 - m1;
    int n3 = r - m2;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* M = (int*)malloc(n2 * sizeof(int));
    int* R = (int*)malloc(n3 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) M[j] = arr[m1 + 1 + j];
    for (int k = 0; k < n3; k++) R[k] = arr[m2 + 1 + k];

    int i = 0, j = 0, k = 0, idx = l;

    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) arr[idx++] = L[i++];
        else if (M[j] <= L[i] && M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) arr[idx++] = L[i++];
        else arr[idx++] = M[j++];
    }

    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }

    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) arr[idx++] = L[i++];
        else arr[idx++] = R[k++];
    }

    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = M[j++];
    while (k < n3) arr[idx++] = R[k++];

    free(L);
    free(M);
    free(R);
}

void mergeSort3(int arr[], int l, int r) {
    if (l >= r) return;

    if (r - l < 2) {
        if (arr[l] > arr[r]) {
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
        }
        return;
    }

    int m1 = l + (r - l) / 3;
    int m2 = l + 2 * (r - l) / 3;

    mergeSort3(arr, l, m1);
    mergeSort3(arr, m1 + 1, m2);
    mergeSort3(arr, m2 + 1, r);

    merge3(arr, l, m1, m2, r);
}

// Main Execution

int main() {
    srand(42);

    FILE *fp = fopen("results2.csv", "w");
    if (fp == NULL) {
        printf("Error opening results2.csv!\n");
        return 1;
    }

    fprintf(fp, "DataStructure,N,ExecutionTime\n");

    int iterations = 10;

    for (int idx = 0; idx < NUM_SIZES; idx++) {
        int n = SIZES[idx];

        int* orig = (int*)malloc(n * sizeof(int));
        int* work = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) orig[i] = rand();

        // 2-Way Merge Sort
        clock_t start = clock();
        for (int iter = 0; iter < iterations; iter++) {
            for (int i = 0; i < n; i++) work[i] = orig[i];
            mergeSort2(work, 0, n - 1);
        }
        clock_t end = clock();
        double time2 = get_time_us(start, end) / iterations;
        fprintf(fp, "Standard 2-Way Merge Sort,%d,%.2f\n", n, time2);

        // 3-Way Merge Sort 
        start = clock();
        for (int iter = 0; iter < iterations; iter++) {
            for (int i = 0; i < n; i++) work[i] = orig[i];
            mergeSort3(work, 0, n - 1);
        }
        end = clock();
        double time3 = get_time_us(start, end) / iterations;
        fprintf(fp, "Modified 3-Way Merge Sort,%d,%.2f\n", n, time3);

        free(orig);
        free(work);

        printf("Completed benchmark for N = %d\n", n);
    }

    fclose(fp);
    printf("\nSuccessfully generated 'results2.csv'!\n");
    return 0;
}
