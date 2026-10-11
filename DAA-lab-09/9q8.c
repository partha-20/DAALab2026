#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

typedef struct {
    int *array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->array = (int *)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
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

void insertMinHeap(MinHeap *heap, int val) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = val;

    while (i != 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int getMin(MinHeap *heap) {
    return heap->array[0];
}

void extractMin(MinHeap *heap) {
    if (heap->size <= 0) return;
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
}

int compareIntervals(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;
    if (i1->start != i2->start)
        return i1->start - i2->start;
    return i1->end - i2->end;
}

int minMeetingRooms(Interval intervals[], int n) {
    if (n <= 0) return 0;

    qsort(intervals, n, sizeof(Interval), compareIntervals);

    MinHeap *heap = createMinHeap(n);

    insertMinHeap(heap, intervals[0].end);

    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= getMin(heap)) {
            extractMin(heap);
        }
        insertMinHeap(heap, intervals[i].end);
    }

    int rooms = heap->size;

    free(heap->array);
    free(heap);

    return rooms;
}

int main() {
    Interval intervals[] = {
        {0, 30},
        {5, 10},
        {15, 20}
    };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    int result = minMeetingRooms(intervals, n);

    printf("%d\n", result);

    return 0;
}