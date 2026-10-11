#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double v;
    double w;
    double lambda;
    double density;
    double taken;
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemB->density > itemA->density) return 1;
    if (itemB->density < itemA->density) return -1;

    if (itemB->lambda > itemA->lambda) return 1;
    if (itemB->lambda < itemA->lambda) return -1;

    return 0;
}

double solveFractionalKnapsackDeterioration(Item items[], int n, double W) {
    for (int i = 0; i < n; i++) {
        items[i].density = items[i].v / items[i].w;
        items[i].taken = 0.0;
    }

    qsort(items, n, sizeof(Item), compare);

    double current_time = 0.0;
    double total_value = 0.0;

    for (int i = 0; i < n; i++) {
        if (current_time >= W) break;

        double remaining_capacity = W - current_time;
        double weight_to_take = (items[i].w <= remaining_capacity) ? items[i].w : remaining_capacity;

        double t1 = current_time;
        double t2 = current_time + weight_to_take;

        double item_value = (items[i].density * weight_to_take) - (0.5 * items[i].lambda * (t2 * t2 - t1 * t1));
        
        total_value += item_value;
        items[i].taken = weight_to_take;
        current_time = t2;
    }

    return total_value;
}

int main() {
    int n = 3;
    double W = 10.0;

    Item items[] = {
        {1, 60.0, 10.0, 0.1, 0.0, 0.0},
        {2, 100.0, 20.0, 0.2, 0.0, 0.0},
        {3, 120.0, 30.0, 0.05, 0.0, 0.0}
    };

    double max_value = solveFractionalKnapsackDeterioration(items, n, W);
    printf("%.2f\n", max_value);

    return 0;
}