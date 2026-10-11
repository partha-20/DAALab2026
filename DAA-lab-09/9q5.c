#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int minCandies(int ratings[], int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int *candies = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    int total_candies = 0;
    for (int i = 0; i < n; i++) {
        total_candies += candies[i];
    }

    free(candies);
    return total_candies;
}

int main() {
    int ratings[] = {1, 0, 2, 8, 5, 2, 1, 4};
    int n = sizeof(ratings) / sizeof(ratings[0]);

    int result = minCandies(ratings, n);

    printf("%d\n", result);

    return 0;
}