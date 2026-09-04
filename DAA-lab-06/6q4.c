#include <stdio.h>
#include <stdlib.h>

long long total_reversal_cost = 0;
int total_reversal_count = 0;

void reverse(int p[], int i, int j) {
    if (i >= j) return;

    int length = j - i + 1;
    total_reversal_cost += length;
    total_reversal_count++;

    while (i < j) {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
        i++;
        j--;
    }
}

void sort_linear_reversals(int p[], int n) {
    for (int i = 0; i < n; i++) {
        int pos = i;
        while (pos < n && p[pos] != i + 1) {
            pos++;
        }
        if (pos != i) {
            reverse(p, i, pos);
        }
    }
}

int count_less_equal(const int p[], int left, int right, int pivot) {
    int cnt = 0;
    for (int i = left; i <= right; i++) {
        if (p[i] <= pivot) cnt++;
    }
    return cnt;
}

void merge_sort_reversals(int p[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort_reversals(p, left, mid);
    merge_sort_reversals(p, mid + 1, right);

    int pivot = left + (right - left) / 2;

    int i = left;
    while (i <= mid && p[i] <= pivot) i++;

    int j = mid + 1;
    while (j <= right && p[j] <= pivot) j++;
    j--;

    if (i <= mid && j >= mid + 1) {
        reverse(p, i, mid);
        reverse(p, mid + 1, j);
        reverse(p, i, j);
    }
}

void print_array(const int p[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", p[i], i == n - 1 ? "" : ", ");
    }
    printf("]\n");
}

int main() {
    int n = 8;
    int original[] = {8, 4, 7, 3, 6, 2, 5, 1};

    int p1[8];
    for (int i = 0; i < n; i++) p1[i] = original[i];

    total_reversal_cost = 0;
    total_reversal_count = 0;

    printf("Original Array: ");
    print_array(original, n);

    sort_linear_reversals(p1, n);
    printf("\n--- Selection Method (O(n) Reversals) ---\n");
    printf("Sorted Array: ");
    print_array(p1, n);
    printf("Reversal Operations: %d\n", total_reversal_count);
    printf("Accumulated Cost:    %lld\n", total_reversal_cost);

    int p2[8];
    for (int i = 0; i < n; i++) p2[i] = original[i];

    total_reversal_cost = 0;
    total_reversal_count = 0;

    merge_sort_reversals(p2, 0, n - 1);
    printf("\n--- Divide & Conquer Method (O(n log^2 n) Cost) ---\n");
    printf("Sorted Array: ");
    print_array(p2, n);
    printf("Reversal Operations: %d\n", total_reversal_count);
    printf("Accumulated Cost:    %lld\n", total_reversal_cost);

    return 0;
}
