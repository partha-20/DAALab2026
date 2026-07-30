#include <stdio.h>

int main() {
    int arr[] = {0, 0, 0, 0, 1, 1, 1, 1};
    int n = 8;
    int low = 0, high = n - 1, mid;
    int ans = -1;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == 1) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (ans != -1) {
        printf("Transition to 1 starts at index: %d\n", ans);
    } else {
        printf("No 1s found in the array.\n");
    }

    return 0;
}