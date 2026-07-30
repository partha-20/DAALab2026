#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[] = {45, 12, 78, 34, 12, 89, 2};
    int n = 7;
    int i;
    int unique = 1;

    qsort(arr, n, sizeof(int), compare);

    for(i = 0; i < n - 1; i++) {
        if(arr[i] == arr[i+1]) {
            unique = 0;
            break;
        }
    }

    if(unique) {
        printf("All elements are unique.\n");
    } else {
        printf("Duplicates found.\n");
    }

    return 0;
}