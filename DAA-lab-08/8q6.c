#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

void editDistanceWithTraceback(const char* A, const char* B) {
    int m = strlen(A);
    int n = strlen(B);

    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min3(dp[i - 1][j],      // Deletion
                                    dp[i][j - 1],      // Insertion
                                    dp[i - 1][j - 1]); // Substitution
            }
        }
    }

    printf("String A: %s\n", A);
    printf("String B: %s\n", B);
    printf("Minimum Edit Distance: %d\n", dp[m][n]);
    printf("Traceback Operations:\n");

    int i = m, j = n;
    char operations[m + n + 1][100];
    int op_count = 0;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            snprintf(operations[op_count++], 100, "Keep '%c'", A[i - 1]);
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            snprintf(operations[op_count++], 100, "Substitute '%c' with '%c'", A[i - 1], B[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            snprintf(operations[op_count++], 100, "Delete '%c' from A", A[i - 1]);
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            snprintf(operations[op_count++], 100, "Insert '%c' into A", B[j - 1]);
            j--;
        }
    }

    for (int k = op_count - 1; k >= 0; k--) {
        printf("  step %d: %s\n", op_count - k, operations[k]);
    }
    printf("\n");

    for (int k = 0; k <= m; k++) free(dp[k]);
    free(dp);
}

int main() {
    printf("Test Case 1:\n");
    editDistanceWithTraceback("kitten", "sitting");

    printf("Test Case 2:\n");
    editDistanceWithTraceback("intention", "execution");

    return 0;
}