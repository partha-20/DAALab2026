#include <stdio.h>
#include <stdlib.h>

typedef enum {
    END = -1,
    START = 1
} EventType;

typedef struct {
    int point;
    EventType type;
} Event;

typedef struct {
    int l;
    int r;
} Interval;

int compareEvents(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->point != e2->point) {
        return e1->point - e2->point;
    }
    return e2->type - e1->type;
}

void findMaxOverlapPoint(Interval S[], int n) {
    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    for (int i = 0; i < n; i++) {
        events[2 * i] = (Event){S[i].l, START};
        events[2 * i + 1] = (Event){S[i].r, END};
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_overlap += events[i].type;

        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = events[i].point;
        }
    }

    printf("Point with maximum overlap: p = %d (contained in %d intervals)\n", best_point, max_overlap);

    free(events);
}

int main() {
    Interval S[] = {{10, 40}, {20, 60}, {50, 90}, {15, 70}};
    int n = sizeof(S) / sizeof(S[0]);

    printf("Input Intervals:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", S[i].l, S[i].r);
    }
    printf("\n\n");

    findMaxOverlapPoint(S, n);

    return 0;
}
