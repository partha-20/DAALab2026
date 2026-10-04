#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void lcs(const char* X, const char* Y) {
    int m = strlen(X);
    int n = strlen(Y);

    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcs_length = dp[m][n];
    
    char* lcs_str = (char*)malloc((lcs_length + 1) * sizeof(char));
    lcs_str[lcs_length] = '\0';

    int i = m, j = n;
    int index = lcs_length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Sequence X: %s\n", X);
    printf("Sequence Y: %s\n", Y);
    printf("LCS Length: %d\n", lcs_length);
    printf("LCS String: %s\n\n", lcs_str);

    free(lcs_str);
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
}

int main() {
    printf("Test Case 1:\n");
    lcs("ABCBDAB", "BDCABA");

    printf("Test Case 2:\n");
    lcs("AGGTAB", "GXTXAYB");

    printf("Test Case 3:\n");
    lcs("AAA", "BBB");

    return 0;
}