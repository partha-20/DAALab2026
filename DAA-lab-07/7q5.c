#include <stdio.h>

void turnOff(int n);
void turnOn(int n);

int moveCount = 0;

void turnOff(int n) {
    if (n <= 0) return;
    if (n == 1) {
        moveCount++;
        return;
    }
    turnOff(n - 2);
    moveCount++; // toggle n
    turnOn(n - 2);
    turnOff(n - 1);
}

void turnOn(int n) {
    if (n <= 0) return;
    if (n == 1) {
        moveCount++;
        return;
    }
    turnOn(n - 1);
    turnOff(n - 2);
    moveCount++; // toggle n
    turnOn(n - 2);
}

int main() {
    int n = 4; // number of switches
    moveCount = 0;
    turnOff(n);
    printf("Minimum moves for %d switches: %d\n", n, moveCount);
    return 0;
}
