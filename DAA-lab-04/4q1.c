#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RED = 0,
    BLUE = 1,
    YELLOW = 2
} Colour;

typedef struct {
    int number;
    Colour colour;
} Item;

const char* getColourName(Colour c) {
    switch (c) {
        case RED: return "Red";
        case BLUE: return "Blue";
        case YELLOW: return "Yellow";
        default: return "Unknown";
    }
}

void sortByColour(Item arr[], int n) {
    Item *output = (Item *)malloc(n * sizeof(Item));
    int count[3] = {0, 0, 0};

    for (int i = 0; i < n; i++) {
        count[arr[i].colour]++;
    }

    int start_blue = count[RED];
    int start_yellow = count[RED] + count[BLUE];

    count[RED] = 0;
    count[BLUE] = start_blue;
    count[YELLOW] = start_yellow;

    for (int i = 0; i < n; i++) {
        Colour c = arr[i].colour;
        output[count[c]] = arr[i];
        count[c]++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}
void printItems(Item arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %-6s) ", arr[i].number, getColourName
               (arr[i].colour));
    }
    printf("\n");
}
int main() {
    Item arr[] = {
        {10, BLUE},{15, RED},
        {20, YELLOW},{25, BLUE},
        {30, RED},{35, YELLOW},
        {40, RED},{45, BLUE}
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array (sorted by number):\n");
    printItems(arr, n);
    sortByColour(arr, n);
    printf("\nSorted array (by colour: Red -> Blue -> Yellow):\n");
    printItems(arr, n);
    return 0;
}
