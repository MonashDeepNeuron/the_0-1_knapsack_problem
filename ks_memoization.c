#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int knapsack_memoization(int ind, int bag_weight, int *weights, int *values, int **max_weight){
    //  Edge case when we have to choose from last ind
    if (ind == 0){
        if (bag_weight >= weights[0]) return values[0];
        return 0;
    }

    if (max_weight[ind][bag_weight] != -1) return max_weight[ind][bag_weight];

    // Max weight till index ind if it is not picked
    int notPick = 0 + knapsack_memoization(ind-1, bag_weight, weights, values, max_weight);
    
    // Max weight till index ind if it is picked
    int pick = INT_MIN;
    if (bag_weight >= weights[ind]){
        pick = values[ind] + knapsack_memoization(ind-1, bag_weight-weights[ind], weights, values, max_weight);
    }

    // Return max of both cases
    return max_weight[ind][bag_weight] = fmax(pick, notPick);
}