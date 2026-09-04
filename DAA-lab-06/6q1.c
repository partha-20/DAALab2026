#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Helper to swap two integers
void swap(int *a, int *b) {
    int* temp = *a;
    *a = *b;
    *b = *temp;
}

// Helper: QuickSort for sorting-dependent operations
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// (i) Finding the maximum element - O(n)
int findMax(const int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// (ii) Finding 1st and 2nd largest elements - O(n)
void findFirstAndSecondLargest(const int arr[], int n, int *first, int *second) {
    *first = arr[0] > arr[1] ? arr[0] : arr[1];
    *second = arr[0] > arr[1] ? arr[1] : arr[0];

    for (int i = 2; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}

// (iii) Finding the mean - O(n)
double findMean(const int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

// (iv) Finding the median using sorting - O(n log n)
double findMedian(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    quickSort(temp, 0, n - 1);

    double median;
    if (n % 2 != 0) {
        median = temp[n / 2];
    } else {
        median = (temp[(n - 1) / 2] + temp[n / 2]) / 2.0;
    }
    free(temp);
    return median;
}

// (v) Finding the standard deviation - O(n)
double findStandardDeviation(const int arr[], int n) {
    double mean = findMean(arr, n);
    double sumSqDiff = 0;
    for (int i = 0; i < n; i++) {
        sumSqDiff += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sumSqDiff / n);
}

// (vi) Finding the mode - O(n log n) time, O(1) extra space
int findMode(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    quickSort(temp, 0, n - 1);

    int mode = temp[0], maxCount = 1, currentCount = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            currentCount++;
        } else {
            currentCount = 1;
        }
        if (currentCount > maxCount) {
            maxCount = currentCount;
            mode = temp[i];
        }
    }
    free(temp);
    return mode;
}

// (vii) Removing all duplicates in-place - O(n^2) time, O(1) space
int removeDuplicates(int arr[], int n) {
    int newSize = 0;
    for (int i = 0; i < n; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < newSize; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            arr[newSize++] = arr[i];
        }
    }
    return newSize;
}

// (viii) Reversing elements in-place - O(n)
void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

// (ix) Partitioning array: elements < pivot come AFTER elements >= pivot - O(n)
int partitionCustom(int arr[], int n, int pivotVal) {
    int left = 0, right = n - 1;
    while (left <= right) {
        while (left <= right && arr[left] >= pivotVal) left++;
        while (left <= right && arr[right] < pivotVal) right--;

        if (left < right) {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    return left; // Index split point
}

void printArray(const int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
    }
    printf("]\n");
}

int main() {
    int rawData[] = {7, 2, 9, 2, 4, 7, 5, 9, 1, 7};
    int n = sizeof(rawData) / sizeof(rawData[0]);

    printf("Original Array (n = %d): ", n);
    printArray(rawData, n);

    printf("\n--- Operational Results ---\n");
    printf("(i)   Max Element: %d\n", findMax(rawData, n));

    int first, second;
    findFirstAndSecondLargest(rawData, n, &first, &second);
    printf("(ii)  1st & 2nd Largest: First = %d, Second = %d\n", first, second);

    printf("(iii) Mean: %.2f\n", findMean(rawData, n));
    printf("(iv)  Median: %.2f\n", findMedian(rawData, n));
    printf("(v)   Standard Deviation: %.2f\n", findStandardDeviation(rawData, n));
    printf("(vi)  Mode: %d\n", findMode(rawData, n));

    // Duplicate removal demo
    int dupArr[10];
    for(int i = 0; i < n; i++) dupArr[i] = rawData[i];
    int newN = removeDuplicates(dupArr, n);
    printf("(vii) Duplicates Removed: ");
    printArray(dupArr, newN);

    // Reversal demo
    int revArr[10];
    for(int i = 0; i < n; i++) revArr[i] = rawData[i];
    reverseArray(revArr, n);
    printf("(viii)Reversed Array: ");
    printArray(revArr, n);

    // Custom Partitioning demo around pivot element value (e.g., pivot = 5)
    int partArr[10];
    for(int i = 0; i < n; i++) partArr[i] = rawData[i];
    int pivotVal = 5;
    partitionCustom(partArr, n, pivotVal);
    printf("(ix)  Partitioned around pivot=%d (>= pivot first, < pivot after): ", pivotVal);
    printArray(partArr, n);

    return 0;
}
