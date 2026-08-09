#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SIZES 6
int SIZES[NUM_SIZES] = {20000, 40000, 60000, 80000, 100000, 120000};

double get_time_us(clock_t start, clock_t end) {
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000000.0;
}

int main() {
    srand(42);

    FILE *fp = fopen("results.csv", "w");
    if (fp == NULL) {
        printf("Error opening file results.csv!\n");
        return 1;
    }

    fprintf(fp, "DataStructure,N,SearchTime\n");

    int iterations = 1000;

    for (int i = 0; i < NUM_SIZES; i++) {
        int n = SIZES[i];

        // 1. Unsorted Array - Linear Search O(n)
        int* u_arr = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) u_arr[j] = j * 2;

        clock_t start = clock();
        for (int iter = 0; iter < iterations; iter++) {
            int target = -1;
            for (int j = 0; j < n; j++) {
                if (u_arr[j] == target) break;
            }
        }
        clock_t end = clock();
        double time_u_arr = get_time_us(start, end) / iterations;
        fprintf(fp, "Unsorted Array O(n),%d,%.4f\n", n, time_u_arr);
        free(u_arr);

        // 2. Sorted Array - Binary Search O(log n)
        int* s_arr = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) s_arr[j] = j * 2;

        start = clock();
        for (int iter = 0; iter < iterations * 100; iter++) {
            int target = n * 2 + 1;
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (s_arr[mid] == target) break;
                if (s_arr[mid] < target) low = mid + 1;
                else high = mid - 1;
            }
        }
        end = clock();
        double time_s_arr = get_time_us(start, end) / (iterations * 100);
        fprintf(fp, "Sorted Array O(log n),%d,%.4f\n", n, time_s_arr);
        free(s_arr);

        // 3. Constant Time Benchmark O(1) - Direct Access / Del
        int* dummy_arr = (int*)malloc(n * sizeof(int));
        start = clock();
        for (int iter = 0; iter < iterations * 1000; iter++) {
            int val = dummy_arr[n / 2];
            (void)val;
        }
        end = clock();
        double time_o1 = get_time_us(start, end) / (iterations * 1000);
        fprintf(fp, "Constant Access O(1),%d,%.4f\n", n, time_o1);
        free(dummy_arr);

        printf("Completed benchmark for N = %d\n", n);
    }

    fclose(fp);
    printf("\nSuccessfully generated 'results.csv'!\n");
    return 0;
}
