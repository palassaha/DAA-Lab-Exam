#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item with weight, profit, and profit/weight ratio
struct item {
    int w; // weight
    int p; // profit
    float r; // profit/weight ratio
};

// Function to read items and knapsack capacity from user input
void read_items(struct item *items, int n, int *capacity) {
    printf("Enter knapsack capacity: ");
    scanf("%d", capacity); // Corrected the way capacity is read
    printf("Enter the weight and profit of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &items[i].w, &items[i].p);
        items[i].r = (float)items[i].p / items[i].w; // Calculate profit/weight ratio
    }
}

// Comparison function for qsort, to sort items by profit/weight ratio in descending order
int compare(const void *a, const void *b) {
    struct item *item1 = (struct item *)a;
    struct item *item2 = (struct item *)b;
    if (item2->r > item1->r) {
        return 1;
    } else if (item2->r < item1->r) {
        return -1;
    } else {
        return 0;
    }
}

// Function to calculate the maximum profit using the fractional knapsack algorithm
float knapsack(struct item *items, int n, int capacity, float *result) {
    float total_profit = 0.0; // Total profit
    qsort(items, n, sizeof(struct item), compare); // Sort items by profit/weight ratio
    for (int i = 0; i < n; i++) {
        result[i] = 0.0; // Initialize the result array
    }
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].w) {
            result[i] = 1.0; // Take the whole item
            capacity -= items[i].w;
            total_profit += items[i].p;
        } else {
            result[i] = (float)capacity / items[i].w; // Take the fraction of the item
            total_profit += result[i] * items[i].p;
            break; // Knapsack is full
        }
    }
    return total_profit;
}

// Function to display the result
void display(struct item *items, float *result, int n, float total_profit) {
    printf("Maximum Profit: %.2f\n", total_profit);
    printf("Result Vector: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", result[i]); // Added space for readability
    }
    printf("\n");
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    struct item *items = (struct item *)malloc(n * sizeof(struct item));
    float *result = (float *)malloc(n * sizeof(float));

    read_items(items, n, &capacity); // Corrected the way capacity is passed
    float total_profit = knapsack(items, n, capacity, result);
    display(items, result, n, total_profit);

    free(items);
    free(result);
    return 0;
}
