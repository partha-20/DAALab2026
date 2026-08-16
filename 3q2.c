#include <stdio.h>
#include <stdlib.h>

int weighings = 0;

int weigh(int coins[], int l1, int r1, int l2, int r2) {
    weighings++;
    int sum1 = 0, sum2 = 0;
    for (int i = l1; i <= r1; i++) sum1 += coins[i];
    for (int i = l2; i <= r2; i++) sum2 += coins[i];
    if (sum1 < sum2) return -1;
    if (sum1 > sum2) return 1;
    return 0;
}

int findDefective(int coins[], int low, int high, int known_good) {
    int len = high - low + 1;
    if (len == 1) {
        if (known_good != -1) {
            int res = weigh(coins, low, low, known_good, known_good);
            if (res < 0) return low;
            return -1;
        }
        return low;
    }

    int half = len / 2;
    int l1 = low, r1 = low + half - 1;
    int l2 = r1 + 1, r2 = r1 + half;

    int result = weigh(coins, l1, r1, l2, r2);

    if (result == 0) {
        if (len % 2 != 0) {
            int extra = high;
            int res = weigh(coins, extra, extra, l1, l1);
            if (res < 0) return extra;
        }
        return -1;
    } else if (result < 0) {
        return findDefective(coins, l1, r1, l2);
    } else {
        return findDefective(coins, l2, r2, l1);
    }
}

int main() {
    int n = 8;
    int coins[] = {10, 10, 10, 9, 10, 10, 10, 10};

    weighings = 0;
    int defective = findDefective(coins, 0, n - 1, -1);

    if (defective != -1)
        printf("Defective coin found at index: %d\n", defective);
    else
        printf("No defective coin found. All coins are perfect.\n");

    printf("Total weighings: %d\n", weighings);
    return 0;
}
