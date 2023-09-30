#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int ks_opti(int n, int bag_weight, int *weights, int *values){
    // Initiliaze 2x1D array of size n * bag_weight+1 with all values = 0
    int *max_weight_0 = (int *)malloc((bag_weight + 1) * sizeof(int));
    memset(max_weight_0, 0, (bag_weight + 1) * sizeof(int));
    int *max_weight_1 = (int *)malloc((bag_weight + 1) * sizeof(int));
    memset(max_weight_1, 0, (bag_weight + 1) * sizeof(int));



    // Initialize first row with weights[0] if bag weight is greater than it at that instance
    // for (int w = 0; w <= bag_weight; w++) max_weight_0[w] = values[0];

    for (int i = 1; i < n; i++) {
        #pragma omp parallel for
        for (int w = 0; w <= bag_weight; w++){
            // Max weight till index ind if it is not picked
            int notPick = 0 + max_weight_0[w];
            
            // Max weight till index ind if it is picked
            int pick = INT_MIN;
            if (bag_weight >= weights[i]){
                pick = values[i] + max_weight_0[w-weights[i]];
            }

            max_weight_1[w] = fmax(pick, notPick);
        }
        memcpy(max_weight_0, max_weight_1, (bag_weight + 1) * sizeof(int));
    }

    int m_w = max_weight_1[bag_weight];

    free(max_weight_0);
    free(max_weight_1);

    return m_w;
}