#include <stdio.h>

int minMovesCoinTriangle(int n) {
    return (n * (n + 1)) / 6;
}

int main() {
    int n = 4; // Number of rows
    printf("Minimum moves for %d rows: %d\n", n, minMovesCoinTriangle(n));
    return 0;
}
