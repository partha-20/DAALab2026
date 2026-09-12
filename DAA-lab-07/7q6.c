#include <stdio.h>

void generateShootingSequence(int n) {
    printf("Shooting sequence for %d hiding spots:\n", n);
    for (int phase = 1; phase <= 2; phase++) {
        for (int i = 2; i <= n - 1; i++) {
            printf("Shoot spot: %d\n", i);
        }
    }
}

int main() {
    int n = 5; // Spots count > 1
    generateShootingSequence(n);
    return 0;
}
