#include <stdio.h>
#include <stdlib.h>

void rodCut(int* P, int n) {
    int* dp = (int*)malloc((n + 1) * sizeof(int));
    int* first_cut = (int*)malloc((n + 1) * sizeof(int));

    if (dp == NULL || first_cut == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    dp[0] = 0;
    first_cut[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        int best_cut = 0;

        for (int j = 1; j <= i; j++) {
            if (P[j - 1] + dp[i - j] > max_val) {
                max_val = P[j - 1] + dp[i - j];
                best_cut = j;
            }
        }

        dp[i] = max_val;
        first_cut[i] = best_cut;
    }

    printf("Rod Length: %d\n", n);
    printf("Maximum Obtainable Revenue: %d\n", dp[n]);
    printf("Optimal Piece Decomposition: ");

    int temp_n = n;
    while (temp_n > 0) {
        printf("%d ", first_cut[temp_n]);
        temp_n -= first_cut[temp_n];
    }
    printf("\n\n");

    free(dp);
    free(first_cut);
}

int main() {
    // Prices for lengths 1 to 8
    int P1[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int n1 = 8;
    printf("Test Case 1:\n");
    rodCut(P1, n1);

    // Prices for lengths 1 to 4
    int P2[] = {2, 5, 7, 8};
    int n2 = 4;
    printf("Test Case 2:\n");
    rodCut(P2, n2);

    // Prices for lengths 1 to 7
    int P3[] = {3, 5, 8, 9, 10, 17, 20};
    int n3 = 7;
    printf("Test Case 3:\n");
    rodCut(P3, n3);

    return 0;
}