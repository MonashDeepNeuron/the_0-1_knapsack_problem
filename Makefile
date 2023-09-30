all: ks_recursive ks_memoization ks_tabulation ks_opti

ks_recursive: knapsack.c ks_recursive.c 
	g++ knapsack.c ks_recursive.c -o ks_recursive -DKS_REC_EXISTS

ks_memoization: knapsack.c ks_memoization.c 
	g++ knapsack.c ks_memoization.c -o ks_memoization -DKS_MEM_EXISTS

ks_tabulation: knapsack.c ks_tabulation.c 
	g++ knapsack.c ks_tabulation.c -o ks_tabulation -DKS_TAB_EXISTS

ks_opti: knapsack.c ks_opti.c
	g++ knapsack.c ks_opti.c -o ks_opti -DKS_OPTI_EXISTS

.PHONY: all