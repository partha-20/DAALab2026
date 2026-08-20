#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Interval;

int compareIntervals(const void *a, const void *b) {
    const Interval *i1 = (const Interval *)a;
    const Interval *i2 = (const Interval *)b;
    return i1->x - i2->x;
}

Interval* mergeIntervals(Interval input[], int n, int *outSize) {
    if (n <= 0) {
        *outSize = 0;
        return NULL;
    }

    qsort(input, n, sizeof(Interval), compareIntervals);

    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    int count = 0;

    merged[count] = input[0];

    for (int i = 1; i < n; i++) {
        if (input[i].x <= merged[count].y) {
            if (input[i].y > merged[count].y) {
                merged[count].y = input[i].y;
            }
        } else {
            count++;
            merged[count] = input[i];
        }
    }

    *outSize = count + 1;
    return merged;
}

void printIntervals(Interval arr[], int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("(%d, %d)", arr[i].x, arr[i].y);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main() {
    Interval I[] = {{1, 3}, {2, 6}, {8, 10}, {7, 18}};
    int n = sizeof(I) / sizeof(I[0]);

    printf("Input intervals:  ");
    printIntervals(I, n);

    int mergedSize = 0;
    Interval *result = mergeIntervals(I, n, &mergedSize);

    printf("Merged intervals: ");
    printIntervals(result, mergedSize);

    free(result);
    return 0;
}
