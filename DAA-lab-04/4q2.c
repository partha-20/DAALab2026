#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
bool findPairWithSum(int S1[], int S2[], int n, int x, int *pair1, int *pair2) {
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);
    int i = 0; int j = n - 1;
    while (i < n && j >= 0) {
        int current_sum = S1[i] + S2[j];
        if (current_sum == x) {
            *pair1 = S1[i];
            *pair2 = S2[j];
            return true;
        } else if (current_sum < x)
            i++;
          else
            j--;
    }
    return false;
}
int main() {
    int n = 5;
    int S1[] = {12, 3, 7, 1, 9};
    int S2[] = {4, 15, 2, 8, 10};
    int x = 17;

    int pair1, pair2;
    bool found = findPairWithSum(S1, S2, n, x, &pair1, &pair2);
    if (found) {
        printf("Found pair: %d (from S1) + %d (from S2) = %d\n", pair1, pair2, x);
    } else {
        printf("No pair found that adds up to %d\n", x);
    }
    return 0;
}
