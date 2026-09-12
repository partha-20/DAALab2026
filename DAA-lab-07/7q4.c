#include <stdio.h>
#include <math.h>

int movesCount = 0;

void hanoi3(int n, char src, char dst, char aux) {
    if (n == 0) return;
    hanoi3(n - 1, src, aux, dst);
    movesCount++;
    hanoi3(n - 1, aux, dst, src);
}

void reves(int n, char src, char dst, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        movesCount++;
        return;
    }
    int k = n - (int)round(sqrt(2 * n + 1)) + 1;
    reves(k, src, aux1, aux2, dst);
    hanoi3(n - k, src, dst, aux2);
    reves(k, aux1, dst, src, aux2);
}

int main() {
    int n = 8;
    movesCount = 0;
    reves(n, 'A', 'B', 'C', 'D');
    printf("Total moves for %d disks: %d\n", n, movesCount);
    return 0;
}
