#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ENTRY = 1,
    EXIT = -1
} EventType;

typedef struct {
    int time;
    EventType type;
} Event;

int compareEvents(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;
    return e1->time - e2->time;
}

void findPeakTime(int entry[], int exit[], int n) {
    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    for (int i = 0; i < n; i++) {
        events[2 * i] = (Event){entry[i], ENTRY};
        events[2 * i + 1] = (Event){exit[i], EXIT};
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current_count = 0;
    int max_count = 0;
    int peak_time = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_count += events[i].type;

        if (current_count > max_count) {
            max_count = current_count;
            peak_time = events[i].time;
        }
    }

    printf("Peak time: %d (with %d people present)\n", peak_time, max_count);

    free(events);
}

int main() {
    int entry[] = {1, 3, 5, 8, 10};
    int exit[]  = {6, 7, 9, 12, 11};
    int n = sizeof(entry) / sizeof(entry[0]);

    findPeakTime(entry, exit, n);

    return 0;
}
