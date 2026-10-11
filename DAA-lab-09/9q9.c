#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int id;
    double weight;
    int is_leaf;
    int depth;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct ListElement {
    Node *node;
    struct ListElement *prev;
    struct ListElement *next;
} ListElement;

Node* createLeafNode(int id, double weight) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->weight = weight;
    node->is_leaf = 1;
    node->depth = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* createInternalNode(double weight, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = -1;
    node->weight = weight;
    node->is_leaf = 0;
    node->depth = 0;
    node->left = left;
    node->right = right;
    return node;
}

void computeDepths(Node *root, int current_depth, int depths[]) {
    if (!root) return;

    root->depth = current_depth;
    if (root->is_leaf) {
        depths[root->id] = current_depth;
        return;
    }

    computeDepths(root->left, current_depth + 1, depths);
    computeDepths(root->right, current_depth + 1, depths);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

double solveHuTucker(double weights[], int n) {
    if (n <= 0) return 0.0;
    if (n == 1) return 0.0;

    ListElement *head = NULL;
    ListElement *tail = NULL;

    for (int i = 0; i < n; i++) {
        ListElement *elem = (ListElement *)malloc(sizeof(ListElement));
        elem->node = createLeafNode(i, weights[i]);
        elem->prev = tail;
        elem->next = NULL;

        if (tail) {
            tail->next = elem;
        } else {
            head = elem;
        }
        tail = elem;
    }

    int active_count = n;

    while (active_count > 1) {
        ListElement *best_i = NULL;
        ListElement *best_j = NULL;
        double min_sum = 1e18;

        ListElement *curr_i = head;
        while (curr_i != NULL) {
            int internal_between = 1;
            ListElement *curr_j = curr_i->next;

            while (curr_j != NULL) {
                if (curr_i->node->is_leaf && curr_j->node->is_leaf && !internal_between) {
                    break;
                }

                double sum = curr_i->node->weight + curr_j->node->weight;
                if (sum < min_sum) {
                    min_sum = sum;
                    best_i = curr_i;
                    best_j = curr_j;
                }

                if (curr_j->node->is_leaf) {
                    internal_between = 0;
                }

                curr_j = curr_j->next;
            }
            curr_i = curr_i->next;
        }

        Node *merged_node = createInternalNode(min_sum, best_i->node, best_j->node);

        best_i->node = merged_node;

        if (best_j->prev) best_j->prev->next = best_j->next;
        if (best_j->next) best_j->next->prev = best_j->prev;
        if (best_j == tail) tail = best_j->prev;

        free(best_j);
        active_count--;
    }

    Node *root = head->node;
    free(head);

    int depths[n];
    computeDepths(root, 0, depths);

    double total_cost = 0.0;
    for (int i = 0; i < n; i++) {
        total_cost += weights[i] * depths[i];
    }

    freeTree(root);
    return total_cost;
}

int main() {
    double weights[] = {10.0, 11.0, 15.0, 12.0, 14.0};
    int n = sizeof(weights) / sizeof(weights[0]);

    double min_cost = solveHuTucker(weights, n);

    printf("%.2f\n", min_cost);

    return 0;
}