#include <stdio.h>
#include <limits.h>

#define MAXCITIES 10

int n;  // Number of cities
int cost[MAXCITIES][MAXCITIES];  // Cost matrix for traveling between cities
int mincost = INT_MAX;  // Minimum cost initialized to a very high value
int minroute[MAXCITIES];  // Array to store the minimum cost route

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate the cost of the current route
void calcost(int route[])
{
    int curcost = 0;
    for(int i = 0; i < n-1; i++)
    {
        curcost += cost[route[i]][route[i+1]];
    }
    curcost += cost[route[n-1]][route[0]];  // Adding cost to return to the starting city
    
    // Update mincost and minroute if a lower cost is found
    if(curcost < mincost)
    {
        mincost = curcost;
        for(int i = 0; i<n; i++)
        {
            minroute[i] = route[i];
        }
    }
}

// Function to generate all permutations of the route array
void permute(int route[], int left, int right)
{
    if(left == right)
    {
        calcost(route);  // Calculate the cost of the current permutation
        return;
    }
    for(int i = left; i <= right; i++)
    {
        swap(&route[left], &route[i]);  // Swap elements to generate permutations
        permute(route, left+1, right);  // Recursively permute the remaining elements
        swap(&route[left], &route[i]);  // Backtrack to restore the original array
    }
}

// Function to display the minimum cost and the corresponding route
void display_mincost_and_route()
{
    printf("\nMinimum cost: %d\n", mincost);
    printf("Route: ");
    for(int i = 0; i < n; i++)
    {
        printf("%d", minroute[i] + 1);  // Convert 0-based index to 1-based index for display
        if(i < n - 1)
        {
            printf("->");
        }
    }
    printf("->%d\n", minroute[0] + 1);  // Return to the starting city
}

int main()
{
    printf("Enter the number of cities: ");
    scanf("%d", &n);

    if(n > MAXCITIES) {
        printf("The number of cities should not exceed %d.\n", MAXCITIES);
        return 1;  // Exit if the number of cities exceeds the defined limit
    }

    printf("Enter the cost matrix (%d * %d): \n", n, n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }

    int route[MAXCITIES];  // Array to store the current route
    for(int i = 0; i < n; i++)
    {
        route[i] = i;  // Initialize the route with the city indices
    }

    permute(route, 0, n-1);  // Generate permutations and calculate the minimum cost
    display_mincost_and_route();  // Display the minimum cost and route

    return 0;
}
