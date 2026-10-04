#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int coinChange(int* coins, int num_coins, int amount) {
    if (amount == 0) return 0;
    
    int max_val = amount + 1; 
    
    int* dp = (int*)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = max_val;
    }
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < num_coins; j++) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    
    int result = (dp[amount] > amount) ? -1 : dp[amount];
    
    free(dp);
    
    return result;
}

int main() {
    int coins1[] = {1, 2, 5};
    int amount1 = 11;
    int n1 = sizeof(coins1) / sizeof(coins1[0]);
    
    printf("Test Case 1:\n");
    printf("Coins: {1, 2, 5}, Target: 11\n");
    printf("Expected: 3 (5 + 5 + 1), Actual: %d\n\n", coinChange(coins1, n1, amount1));

    int coins2[] = {2};
    int amount2 = 3;
    int n2 = sizeof(coins2) / sizeof(coins2[0]);
    
    printf("Test Case 2:\n");
    printf("Coins: {2}, Target: 3\n");
    printf("Expected: -1, Actual: %d\n\n", coinChange(coins2, n2, amount2));
    
    int coins3[] = {1, 2, 5};
    int amount3 = 0;
    int n3 = sizeof(coins3) / sizeof(coins3[0]);
    
    printf("Test Case 3:\n");
    printf("Coins: {1, 2, 5}, Target: 0\n");
    printf("Expected: 0, Actual: %d\n", coinChange(coins3, n3, amount3));

    return 0;
}