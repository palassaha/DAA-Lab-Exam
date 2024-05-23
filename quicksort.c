#include<stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array
int partition(int arr[], int l, int h)
{
    int i = l - 1;
    int pivot = arr[h]; // Choosing the last element as the pivot
    for(int j = l; j < h; j++) // Iterate over the array
    {
        if(arr[j] <= pivot) // If current element is smaller than or equal to pivot
        {
            i++;
            swap(&arr[i], &arr[j]); // Swap elements
        }
    }
    swap(&arr[i + 1], &arr[h]); // Swap the pivot element to its correct position
    return i + 1; // Return the partition index
}

// Function to perform quicksort
void quicksort(int arr[], int l, int h)
{
    if(l < h) // Base condition
    {
        int pi = partition(arr, l, h); // Partition the array
        quicksort(arr, l, pi - 1); // Recursively sort the left subarray
        quicksort(arr, pi + 1, h); // Recursively sort the right subarray
    }
}

// Function to display the array
void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main()
{
    int arr[9] = {1, 5, 0, 8, 46, 88, 7, 11, 20}; // Initialize the array
    int n = sizeof(arr) / sizeof(arr[0]); // Calculate the number of elements
    printf("Before Sorting: ");
    display(arr, n); // Display the array before sorting
    quicksort(arr, 0, n - 1); // Sort the array using quicksort
    printf("After Sorting: ");
    display(arr, n); // Display the array after sorting
    return 0;
}
