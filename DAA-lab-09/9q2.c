#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct MinHeap {
    int size;
    int capacity;
    Node **array;
} MinHeap;

typedef struct SymbolCode {
    char symbol;
    int freq;
    int len;
    unsigned int code;
} SymbolCode;

Node* createNode(char symbol, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*));
    return minHeap;
}

void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

Node* buildHuffmanTree(char symbols[], int freqs[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = createNode(symbols[i], freqs[i]);
    }
    minHeap->size = size;

    for (int i = (minHeap->size - 2) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    Node* root = extractMin(minHeap);
    free(minHeap->array);
    free(minHeap);
    return root;
}

void getCodeLengths(Node* root, int depth, SymbolCode symCodes[], int* count) {
    if (!root) return;

    if (!root->left && !root->right) {
        symCodes[*count].symbol = root->symbol;
        symCodes[*count].freq = root->freq;
        symCodes[*count].len = (depth == 0) ? 1 : depth;
        (*count)++;
        return;
    }

    getCodeLengths(root->left, depth + 1, symCodes, count);
    getCodeLengths(root->right, depth + 1, symCodes, count);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int compareCanonical(const void* a, const void* b) {
    SymbolCode* s1 = (SymbolCode*)a;
    SymbolCode* s2 = (SymbolCode*)b;

    if (s1->len != s2->len)
        return s1->len - s2->len;
    return s1->symbol - s2->symbol;
}

void printBinary(unsigned int code, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", (code >> i) & 1);
    }
}

void buildCanonicalCodes(SymbolCode symCodes[], int n) {
    qsort(symCodes, n, sizeof(SymbolCode), compareCanonical);

    unsigned int currentCode = 0;
    symCodes[0].code = currentCode;

    for (int i = 1; i < n; i++) {
        currentCode = (currentCode + 1) << (symCodes[i].len - symCodes[i - 1].len);
        symCodes[i].code = currentCode;
    }
}

int main() {
    char symbols[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(symbols) / sizeof(symbols[0]);

    Node* root = buildHuffmanTree(symbols, freqs, n);

    SymbolCode symCodes[n];
    int count = 0;
    getCodeLengths(root, 0, symCodes, &count);

    buildCanonicalCodes(symCodes, n);

    printf("Symbol | Freq | Length | Canonical Code\n");
    printf("-------+------+--------+---------------\n");
    double totalBits = 0.0;
    double totalFreq = 0.0;

    for (int i = 0; i < n; i++) {
        printf("   %c   | %4d |   %2d   | ", symCodes[i].symbol, symCodes[i].freq, symCodes[i].len);
        printBinary(symCodes[i].code, symCodes[i].len);
        printf("\n");
        totalBits += symCodes[i].freq * symCodes[i].len;
        totalFreq += symCodes[i].freq;
    }

    printf("\nExpected Length (bits/symbol): %.4f\n", totalBits / totalFreq);

    freeTree(root);
    return 0;
}