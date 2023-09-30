#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Knapsack recursive function
int knapsack_recursive(int ind, int bag_weight, int *weights, int *values){
    //  Edge case when we have to choose from last ind
    if (ind == 0){
        if (bag_weight >= weights[0]) return values[0];
        return 0;
    }

    // Max weight till index ind if it is not picked
    int notPick = 0 + knapsack_recursive(ind-1, bag_weight, weights, values);
    
    // Max weight till index ind if it is picked
    int pick = INT_MIN;
    if (bag_weight >= weights[ind]){
        pick = values[ind] + knapsack_recursive(ind-1, bag_weight-weights[ind], weights, values);
    }

    // Return max of both cases
    return fmax(pick, notPick);
}