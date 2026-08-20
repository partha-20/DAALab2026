#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool kSumHelper(int S[], int n, int k, long long target, int start, int result[]) {
    if (k == 2) {
        int left = start;
        int right = n - 1;

        while (left < right) {
            long long current_sum = (long long)S[left] + S[right];
            if (current_sum == target) {
                result[0] = S[left];
                result[1] = S[right];
                return true;
            } else if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return false;
    }

    for (int i = start; i <= n - k; i++) {
        result[k - 1] = S[i];
        if (kSumHelper(S, n, k - 1, target - S[i], i + 1, result)) {
            return true;
        }
    }

    return false;
}

bool hasKSum(int S[], int n, int k, long long T, int result[]) {
    qsort(S, n, sizeof(int), compare);
    return kSumHelper(S, n, k, T, 0, result);
}

int main() {
    int S[] = {14, 3, 27, 8, 1, 9, 12, 5};
    int n = sizeof(S) / sizeof(S[0]);
    int k = 4;
    long long T = 30;
    int result[4];

    if (hasKSum(S, n, k, T, result)) {
        printf("Found %d elements that add up to %lld: ", k, T);
        for (int i = 0; i < k; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("No %d elements add up to %lld\n", k, T);
    }

    return 0;
}
