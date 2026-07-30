#include <stdio.h>

int moves = 0;

void hanoi(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source, target);
        moves++;
        return;
    }
    hanoi(n - 1, source, auxiliary, target);
    printf("Move disk %d from %c to %c\n", n, source, target);
    moves++;
    hanoi(n - 1, auxiliary, target, source);
}

int main() {
    int n = 3;
    moves = 0;
    printf("Solving for %d disks:\n", n);
    hanoi(n, 'A', 'C', 'B');
    printf("Total moves: %d\n", moves);
    return 0;
}