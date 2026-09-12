#include <stdio.h>
#include <limits.h>

int max(int a, int b) { return (a > b) ? a : b; }

int superEggDrop(int E, int F) {
    int dp[E + 1][F + 1];
    for (int i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int j = 1; j <= F; j++) {
        dp[1][j] = j;
    }

    for (int i = 2; i <= E; i++) {
        for (int j = 2; j <= F; j++) {
            dp[i][j] = INT_MAX;
            for (int k = 1; k <= j; k++) {
                int res = 1 + max(dp[i - 1][k - 1], dp[i][j - k]);
                if (res < dp[i][j]) {
                    dp[i][j] = res;
                }
            }
        }
    }
    return dp[E][F];
}

int main() {
    int E = 2, F = 100;
    printf("Minimum drops for E=%d, F=%d: %d\n", E, F, superEggDrop(E, F));
    return 0;
}
