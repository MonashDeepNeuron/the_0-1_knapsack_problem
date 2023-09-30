#!/bin/bash

g++ knapsack.c ks_recursive.c -o ks_recursive
g++ knapsack.c ks_memoization.c -o ks_memoization
