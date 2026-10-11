#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
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

void maxHeapify(MaxHeap *heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left] > heap->array[largest])
        largest = left;

    if (right < heap->size && heap->array[right] > heap->array[largest])
        largest = right;

    if (largest != idx) {
        swap(&heap->array[largest], &heap->array[idx]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap *heap, int val) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = val;

    while (i != 0 && heap->array[(i - 1) / 2] < heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMax(MaxHeap *heap) {
    if (heap->size <= 0) return -1;
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    int root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return root;
}

int minDeviation(int nums[], int n) {
    MaxHeap *heap = createMaxHeap(n);
    int min_val = 2147483647;

    for (int i = 0; i < n; i++) {
        int val = nums[i];
        if (val % 2 != 0) {
            val *= 2;
        }
        insertMaxHeap(heap, val);
        if (val < min_val) {
            min_val = val;
        }
    }

    int min_deviation = heap->array[0] - min_val;

    while (heap->size > 0) {
        int max_val = extractMax(heap);
        int current_dev = max_val - min_val;

        if (current_dev < min_deviation) {
            min_deviation = current_dev;
        }

        if (max_val % 2 == 0) {
            int new_val = max_val / 2;
            insertMaxHeap(heap, new_val);
            if (new_val < min_val) {
                min_val = new_val;
            }
        } else {
            break;
        }
    }

    free(heap->array);
    free(heap);

    return min_deviation;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);

    int result = minDeviation(nums, n);
    printf("%d\n", result);

    return 0;
}