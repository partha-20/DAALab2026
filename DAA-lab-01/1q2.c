#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int trials = 100000;
    int fair_heads = 0, biased_heads = 0;
    int i;

    srand(time(NULL));

    for(i = 0; i < trials; i++) {
        if(rand() % 2 == 0) {
            fair_heads++;
        }
    }

    for(i = 0; i < trials; i++) {
        if((rand() % 100) < 75) {
            biased_heads++;
        }
    }

    printf("Fair Coin HEAD Probability: %f\n", (double)fair_heads / trials);
    printf("Biased Coin HEAD Probability: %f\n", (double)biased_heads / trials);

    return 0;
}