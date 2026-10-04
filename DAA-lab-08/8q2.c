#include <stdio.h>
#include <stdlib.h>

int change(int amount, int* coins, int coinsSize) {
    if (amount == 0) return 1;

    unsigned long long* dp = (unsigned long long*)calloc(amount + 1, sizeof(unsigned long long));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    dp[0] = 1;

    for (int i = 0; i < coinsSize; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    int result = (int)dp[amount];
    free(dp);

    return result;
}

int main() {
    int coins1[] = {1, 2, 5};
    int amount1 = 5;
    int n1 = sizeof(coins1) / sizeof(coins1[0]);

    printf("Test Case 1:\n");
    printf("Coins: {1, 2, 5}, Target: 5\n");
    printf("Expected: 4, Actual: %d\n\n", change(amount1, coins1, n1));

    int coins2[] = {2};
    int amount2 = 3;
    int n2 = sizeof(coins2) / sizeof(coins2[0]);

    printf("Test Case 2:\n");
    printf("Coins: {2}, Target: 3\n");
    printf("Expected: 0, Actual: %d\n\n", change(amount2, coins2, n2));

    int coins3[] = {10};
    int amount3 = 10;
    int n3 = sizeof(coins3) / sizeof(coins3[0]);

    printf("Test Case 3:\n");
    printf("Coins: {10}, Target: 10\n");
    printf("Expected: 1, Actual: %d\n", change(amount3, coins3, n3));

    return 0;
}