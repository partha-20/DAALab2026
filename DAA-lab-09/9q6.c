#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct {
    char ch;
    int freq;
} CharFreq;

typedef struct {
    CharFreq *array;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->array = (CharFreq *)malloc(capacity * sizeof(CharFreq));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(CharFreq *a, CharFreq *b) {
    CharFreq temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].freq > heap->array[largest].freq)
        largest = left;

    if (right < heap->size && heap->array[right].freq > heap->array[largest].freq)
        largest = right;

    if (largest != idx) {
        swap(&heap->array[largest], &heap->array[idx]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap *heap, CharFreq item) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = item;

    while (i != 0 && heap->array[(i - 1) / 2].freq < heap->array[i].freq) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

CharFreq extractMax(MaxHeap *heap) {
    CharFreq root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return root;
}

char* rearrangeString(char *s, int k) {
    int n = strlen(s);
    if (k <= 1 || n <= 1) {
        char *result = (char *)malloc((n + 1) * sizeof(char));
        strcpy(result, s);
        return result;
    }

    int counts[MAX_CHAR] = {0};
    for (int i = 0; i < n; i++) {
        counts[(unsigned char)s[i]]++;
    }

    MaxHeap *heap = createMaxHeap(MAX_CHAR);
    for (int i = 0; i < MAX_CHAR; i++) {
        if (counts[i] > 0) {
            CharFreq item = {(char)i, counts[i]};
            insertMaxHeap(heap, item);
        }
    }

    char *result = (char *)malloc((n + 1) * sizeof(char));
    CharFreq *cooldown = (CharFreq *)malloc(k * sizeof(CharFreq));
    int cool_head = 0, cool_tail = 0, cool_count = 0;

    for (int i = 0; i < n; i++) {
        if (i >= k) {
            CharFreq released = cooldown[cool_head];
            cool_head = (cool_head + 1) % k;
            cool_count--;
            if (released.freq > 0) {
                insertMaxHeap(heap, released);
            }
        }

        if (heap->size == 0) {
            free(result);
            free(cooldown);
            free(heap->array);
            free(heap);
            char *empty = (char *)malloc(1 * sizeof(char));
            empty[0] = '\0';
            return empty;
        }

        CharFreq current = extractMax(heap);
        result[i] = current.ch;
        current.freq--;

        cooldown[cool_tail] = current;
        cool_tail = (cool_tail + 1) % k;
        cool_count++;
    }

    result[n] = '\0';

    free(cooldown);
    free(heap->array);
    free(heap);

    return result;
}

int main() {
    char s[] = "aabbcc";
    int k = 3;

    char *res = rearrangeString(s, k);
    printf("%s\n", res);
    free(res);

    return 0;
}