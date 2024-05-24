#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
struct edge {
    int source;
    int destination;
    int weight;
};

// Structure to represent a graph
struct graph {
    int v;  // Number of vertices
    int e;  // Number of edges
    struct edge *edge;  // Array of edges
};

// Function to create a graph
struct graph* creategraph(int v, int e) {
    struct graph *g;
    g = (struct graph*)malloc(sizeof(struct graph));
    g->v = v;
    g->e = e;
    g->edge = (struct edge*)malloc(g->e * sizeof(struct edge));
    return g;
}

// Function to display the solution
void displaysoln(int dist[], int n, int flag) {
    int i;
    if (flag) {
        printf("\nVertex\tDistance from source vertex\n");
        for (i = 0; i < n; ++i) {
            printf("%d\t\t%d\n", i, dist[i]);
        }
        printf("This graph contains no negative edge cycle\n");
    } else {
        printf("This graph contains a negative edge cycle\n");
    }
}

// Function to implement the Bellman-Ford algorithm
void BellmanFord(struct graph *g, int source) {
    int i, j, u, v, w, flag = 1;
    int vertices = g->v;
    int edges = g->e;
    int storedist[vertices];

    // Initialize distances from source to all other vertices as INFINITE
    for (i = 0; i < vertices; i++) {
        storedist[i] = INT_MAX;
    }
    storedist[source] = 0; 

    // Relax all edges |V| - 1 times
    for (i = 1; i <= vertices - 1; i++) {
        for (j = 0; j < edges; j++) {
            u = g->edge[j].source;
            v = g->edge[j].destination;
            w = g->edge[j].weight;
            if (storedist[u] != INT_MAX && storedist[u] + w < storedist[v]) {
                storedist[v] = storedist[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    for (i = 0; i < edges; i++) {
        u = g->edge[i].source;
        v = g->edge[i].destination;
        w = g->edge[i].weight;
        if (storedist[u] != INT_MAX && storedist[u] + w < storedist[v]) {
            flag = 0;
        }
    }

    displaysoln(storedist, vertices, flag);
}

int main() {
    int v, e, s, i;
    printf("Enter number of vertices in the graph\n");
    scanf("%d", &v);
    printf("Enter number of edges in the graph\n");
    scanf("%d", &e);
    printf("Enter source vertex number\n");
    scanf("%d", &s);
    
    struct graph *gp = creategraph(v, e);

    // Read edge properties
    for (i = 0; i < e; i++) {
        printf("\nEnter edge %d properties: source, destination, weight respectively\n", i + 1);
        scanf("%d", &gp->edge[i].source);
        scanf("%d", &gp->edge[i].destination);
        scanf("%d", &gp->edge[i].weight);
    }

    // Execute Bellman-Ford algorithm
    BellmanFord(gp, s);
    
    // Free allocated memory
    free(gp->edge);
    free(gp);
    
    return 0;
}
