#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long *array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->array = (long long *)malloc(capacity * sizeof(long long));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left] < heap->array[smallest])
        smallest = left;

    if (right < heap->size && heap->array[right] < heap->array[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap *heap, long long val) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = val;

    while (i != 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

long long extractMin(MinHeap *heap) {
    if (heap->size <= 0) return 0;
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    long long root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return root;
}

long long minCostToConnectSticks(long long sticks[], int n) {
    if (n <= 1) return 0;

    MinHeap *heap = createMinHeap(n);

    for (int i = 0; i < n; i++) {
        heap->array[i] = sticks[i];
    }
    heap->size = n;

    for (int i = (heap->size - 2) / 2; i >= 0; i--) {
        minHeapify(heap, i);
    }

    long long total_cost = 0;

    while (heap->size > 1) {
        long long first = extractMin(heap);
        long long second = extractMin(heap);

        long long current_cost = first + second;
        total_cost += current_cost;

        insertMinHeap(heap, current_cost);
    }

    free(heap->array);
    free(heap);

    return total_cost;
}

int main() {
    long long sticks[] = {2, 4, 3, 1, 8};
    int n = sizeof(sticks) / sizeof(sticks[0]);

    long long min_cost = minCostToConnectSticks(sticks, n);

    printf("%lld\n", min_cost);

    return 0;
}