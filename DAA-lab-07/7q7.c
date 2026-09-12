#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type; // -1 for death, +1 for birth
} Event;

int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->year != e2->year)
        return e1->year - e2->year;
    return e1->type - e2->type; // -1 comes before +1
}

void findBestTime(int births[], int deaths[], int n) {
    Event events[2 * n];
    for (int i = 0; i < n; i++) {
        events[2 * i] = (Event){births[i], 1};
        events[2 * i + 1] = (Event){deaths[i], -1};
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int maxAlive = 0, currentAlive = 0, bestYear = -1;
    for (int i = 0; i < 2 * n; i++) {
        currentAlive += events[i].type;
        if (currentAlive > maxAlive) {
            maxAlive = currentAlive;
            bestYear = events[i].year;
        }
    }
    printf("Year with most scientists alive: %d (Total: %d)\n", bestYear, maxAlive);
}

int main() {
    int births[] = {1879, 1643, 1856};
    int deaths[] = {1955, 1727, 1943};
    int n = 3;
    findBestTime(births, deaths, n);
    return 0;
}
