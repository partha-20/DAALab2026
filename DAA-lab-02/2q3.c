#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_K 6
int K_SIZES[NUM_K] = {10, 20, 30, 40, 50, 60};
#define N_ELEM 5000

double get_time_us(clock_t start, clock_t end) {
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0;
}

void merge(int arr1[], int size1, int arr2[], int size2, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) out[k++] = arr1[i++];
        else out[k++] = arr2[j++];
    }
    while (i < size1) out[k++] = arr1[i++];
    while (j < size2) out[k++] = arr2[j++];
}

void method1_iterative_merge(int** arrays, int k, int n, int* result) {
    int current_size = n;
    for (int i = 0; i < n; i++) result[i] = arrays[0][i];

    for (int i = 1; i < k; i++) {
        int* temp = (int*)malloc((current_size + n) * sizeof(int));
        merge(result, current_size, arrays[i], n, temp);
        current_size += n;
        for (int j = 0; j < current_size; j++) result[j] = temp[j];
        free(temp);
    }
}

void method2_pairwise_merge(int** arrays, int k, int n, int* result) {
    int** current_arrays = (int**)malloc(k * sizeof(int*));
    int* sizes = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        current_arrays[i] = (int*)malloc(n * sizeof(int));
        sizes[i] = n;
        for (int j = 0; j < n; j++) current_arrays[i][j] = arrays[i][j];
    }

    int active_k = k;
    while (active_k > 1) {
        int new_k = (active_k + 1) / 2;
        int** next_arrays = (int**)malloc(new_k * sizeof(int*));
        int* next_sizes = (int*)malloc(new_k * sizeof(int));

        for (int i = 0; i < active_k; i += 2) {
            if (i + 1 < active_k) {
                int merged_size = sizes[i] + sizes[i + 1];
                next_arrays[i / 2] = (int*)malloc(merged_size * sizeof(int));
                next_sizes[i / 2] = merged_size;
                merge(current_arrays[i], sizes[i], current_arrays[i + 1], sizes[i + 1], next_arrays[i / 2]);
                free(current_arrays[i]);
                free(current_arrays[i + 1]);
            } else {
                next_arrays[i / 2] = current_arrays[i];
                next_sizes[i / 2] = sizes[i];
            }
        }

        free(current_arrays);
        free(sizes);
        current_arrays = next_arrays;
        sizes = next_sizes;
        active_k = new_k;
    }

    for (int j = 0; j < sizes[0]; j++) result[j] = current_arrays[0][j];
    free(current_arrays[0]);
    free(current_arrays);
    free(sizes);
}

int main() {
    srand(42);

    FILE *fp = fopen("results3.csv", "w");
    if (fp == NULL) {
        printf("Error opening results3.csv!\n");
        return 1;
    }

    fprintf(fp, "DataStructure,K,ExecutionTime\n");

    for (int idx = 0; idx < NUM_K; idx++) {
        int k = K_SIZES[idx];
        int n = N_ELEM;

        int** arrays = (int**)malloc(k * sizeof(int*));
        for (int i = 0; i < k; i++) {
            arrays[i] = (int*)malloc(n * sizeof(int));
            int base = rand() % 10;
            for (int j = 0; j < n; j++) {
                base += rand() % 5;
                arrays[i][j] = base;
            }
        }

        int* result1 = (int*)malloc(k * n * sizeof(int));
        int* result2 = (int*)malloc(k * n * sizeof(int));

        clock_t start = clock();
        method1_iterative_merge(arrays, k, n, result1);
        clock_t end = clock();
        double time1 = get_time_us(start, end);
        fprintf(fp, "Method 1 Iterative O(nk^2),%d,%.2f\n", k, time1);

        start = clock();
        method2_pairwise_merge(arrays, k, n, result2);
        end = clock();
        double time2 = get_time_us(start, end);
        fprintf(fp, "Method 2 Pairwise O(nk log k),%d,%.2f\n", k, time2);

        for (int i = 0; i < k; i++) free(arrays[i]);
        free(arrays);
        free(result1);
        free(result2);

        printf("Completed benchmark for K = %d\n", k);
    }

    fclose(fp);
    printf("\nSuccessfully generated 'results3.csv'!\n");
    return 0;
}
