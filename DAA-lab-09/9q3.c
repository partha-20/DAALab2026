#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double distance;
    double fuel;
} Station;

typedef struct {
    double *array;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->array = (double *)malloc(capacity * sizeof(double));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(double *a, double *b) {
    double temp = *a;
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

void insertMaxHeap(MaxHeap *heap, double fuel) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = fuel;

    while (i != 0 && heap->array[(i - 1) / 2] < heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

double extractMax(MaxHeap *heap) {
    if (heap->size <= 0) return -1.0;
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    double root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return root;
}

int compareStations(const void *a, const void *b) {
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;
    if (s1->distance < s2->distance) return -1;
    if (s1->distance > s2->distance) return 1;
    return 0;
}

int minRefuelStops(double D, double F, Station stations[], int n) {
    qsort(stations, n, sizeof(Station), compareStations);

    MaxHeap *maxHeap = createMaxHeap(n + 1);
    
    double current_reach = F;
    int stops = 0;
    int i = 0;

    while (current_reach < D) {
        while (i < n && stations[i].distance <= current_reach) {
            insertMaxHeap(maxHeap, stations[i].fuel);
            i++;
        }

        if (maxHeap->size == 0) {
            free(maxHeap->array);
            free(maxHeap);
            return -1;
        }

        double max_fuel = extractMax(maxHeap);
        current_reach += max_fuel;
        stops++;
    }

    free(maxHeap->array);
    free(maxHeap);
    return stops;
}

int main() {
    double D = 100.0;
    double F = 10.0;

    Station stations[] = {
        {10.0, 60.0},
        {20.0, 30.0},
        {30.0, 30.0},
        {60.0, 40.0}
    };
    int n = sizeof(stations) / sizeof(stations[0]);

    int result = minRefuelStops(D, F, stations, n);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }

    return 0;
}