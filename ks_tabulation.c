#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int knapsack_tabulation(int n, int bag_weight, int *weights, int *values){
    // Initiliaze 2D array of size n * bag_weight+1 with all values = 0 for tabulation
    int **max_weight = (int **)malloc(n * sizeof(int *));
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        max_weight[i] = (int *)malloc((bag_weight + 1) * sizeof(int));
        memset(max_weight[i], 0, (bag_weight + 1) * sizeof(int));
    }

    // Initialize first row with weights[0] if bag weight is greater than it at that instance
    for (int w = 0; w <= bag_weight; w++) max_weight[0][w] = values[0];

    for (int i = 1; i < n; i++) {
        #pragma omp parallel for
        for (int w = 0; w <= bag_weight; w++){
            // Max weight till index ind if it is not picked
            int notPick = 0 + max_weight[i-1][w];
            
            // Max weight till index ind if it is picked
            int pick = INT_MIN;
            if (bag_weight >= weights[i]){
                pick = values[i] + max_weight[i-1][w-weights[i]];
            }

            max_weight[i][w] = fmax(pick, notPick);
        }
    }

    int m_w = max_weight[n-1][bag_weight];

    free(max_weight);

    return m_w;
}