#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include "ks_tabulation.h"


// Function to generate an array of random numbers containing numbers between num_lower and num upper
int * generate_num_arr(int n, int num_lower, int num_upper){
    // Set seed to generate random items
    srand(time(NULL));

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        arr[i] = (rand()%num_upper) + num_lower;
    }

    return arr;
}

// knapsack_recursive function declaration
int knapsack_recursive(int ind, int bag_weight, int *weights, int *values);

// knapsack_memoization fn declaration
int knapsack_memoization(int ind, int bag_weight, int *weights, int *values, int **max_weight);

// knapsack_optimised fn declaration
int ks_opti(int n, int bag_weight, int *weights, int *values);

int main(){

    // Get number of items to be generated
    int n = 10000;
    // printf("Enter number of items :");
    // scanf("%d", &n);

    // Get weight and value arrays
    int *weights = generate_num_arr(n, 1, 10);
    int *values = generate_num_arr(n, 100, 500);

    // for (int i = 0; i < n; i++){
    //     printf("%d %d\n", weights[i], values[i]);
    // }

    int bag_weight = 100000;
    // printf("Enter bag weight :");
    // scanf("%d", &bag_weight);

    //  Recursive knapsack function
    #ifdef KS_REC_EXISTS
        int max_value = knapsack_recursive(n-1, bag_weight, weights, values);
        printf("Max value = %d\n", max_value);
    #endif


    //  Memoized knapsack function
    #ifdef KS_MEM_EXISTS
        // Initiliaze 2D array of size n * bag_weight+1 with all values = -1 for memoization
        int **max_weight = (int **)malloc(n * sizeof(int *));
        #pragma omp parallel for
        for (int i = 0; i < n; i++){
            max_weight[i] = (int *)malloc((bag_weight + 1) * sizeof(int));
            memset(max_weight[i], -1, (bag_weight + 1) * sizeof(int));
        }

        // Call memoized recursive knapsack function 
        int max_value = knapsack_memoization(n-1, bag_weight, weights, values, max_weight);

        printf("Max value = %d\n", max_value);
        free(max_weight);
    #endif

    #ifdef KS_TAB_EXISTS
        int max_value = knapsack_tabulation(n, bag_weight, weights, values);
        printf("Max value = %d\n", max_value);    
    #endif

    #ifdef KS_OPTI_EXISTS
        int max_value = ks_opti(n, bag_weight, weights, values);
        printf("Max value = %d\n", max_value);    
    #endif
    
    free(weights);
    free(values);
    return 0;
}