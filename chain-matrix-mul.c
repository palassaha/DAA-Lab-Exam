#include <stdio.h>
#include <limits.h>
#define INFY 999999999

// Matrix to store minimum number of multiplications
long int m[20][20];
// Matrix to store the split point
int s[20][20];
// Array to store the dimensions of matrices
int p[20];

// Function to print the optimal multiplication sequence
void print_optimal(int i, int j) {
    if (i == j) {
        printf("A%d", i);  // Base case: single matrix
    } else {
        printf("(");
        print_optimal(i, s[i][j]);        // Print left side of split
        print_optimal(s[i][j] + 1, j);    // Print right side of split
        printf(")");
    }
}

// Function to calculate the minimum multiplication cost
void matrix_chain_mult(int n) {
    long int q;
    int i, j, k, l;

    // Initialize the main diagonal to 0 (cost of multiplying one matrix is 0)
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // l is the chain length (from 2 to n)
    for (l = 2; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;  // Ending index of the chain
            m[i][j] = INFY; // Initialize with a large number

            // Iterate over all possible splits
            for (k = i; k < j; k++) {
                // Calculate cost of splitting at k
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                // Update minimum cost and split point
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int n, i, j;

    // Input number of matrices
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    // Input dimensions of matrices
    printf("\nEnter the dimensions:\n");
    for (i = 0; i <= n; i++) {
        printf("P%d: ", i);
        scanf("%d", &p[i]);
    }

    // Compute the optimal order
    matrix_chain_mult(n);

    // Output the cost matrix
    printf("\n-----Cost Matrix-----\n");
    for (i = 1; i <= n; i++) {
        for (j = i; j <= n; j++) {
            printf("m[%d][%d] : %ld\n", i, j, m[i][j]);
        }
    }

    // Output the optimal multiplication sequence
    printf("\n-----Multiplication Sequence-----\n");
    print_optimal(1, n);
    printf("\n");

    // Output the minimum number of multiplications required
    printf("\nMinimum number of multiplications required is: %ld\n", m[1][n]);
    return 0;
}
