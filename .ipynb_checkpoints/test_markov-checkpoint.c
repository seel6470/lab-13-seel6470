///////////////////////////////////////////////////////////////////////////////
// test_markov.c
///////////////////////////////////////////////////////////////////////////////
// Author:  Seth Ely
// Date:    11/26/2024
///////////////////////////////////////////////////////////////////////////////
// Description:
//   Test program to show the usage of the Markov structure and its operations.
//   The program performs 15 updates to the markov chain structure and prints
//   the updated matrix each time, including the max and min rows at certain
//   updates. It also shows the matrix multiplication operation that can be used
//   to show the probability of a state transitioning from i to j in multiple
//   moves (M^k[i][j] represents the probability i transitions to j in k steps).
//
// Usage:
//    - Compile by running `make` in the root directory and run ./test_markov
//      to see the results.
//
// NOTE:
//   A Markov Chain should always sum to 1, however for the sake of simplicity,
//   all indices in the matrix are initialized to 0. In this circumstance, the
//   probabilies of state change from i to j will be equal (albeit 0) and the
//   most probabilistic outcome can be computed the same. As soon as an update
//   to any row occurs, the index for the first state change is equal to 1, all
//   others being 0. This returns the correct most probable state change (and
//   least probable state changes are tied to 0).
//
//   With each additional update, the indices in each row represent the ratio
//   of each transition from state i to state j over all transitions from
//   state i.
//   
///////////////////////////////////////////////////////////////////////////////

#include "markov.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
// main()
//
//  Demonstrates the functionality of the Markov structure using the given
//  functions, initializing, updating, printing and detecting the max/min of
//  specific rows.
//
// Parameters:
//    - None
//
// Returns:
//    - 0 if the program runs successfully.
///////////////////////////////////////////////////////////////////////////////
int main() {
    int size = 3;   // Size of the matrix
    int power = 2;  // Power to raise the matrix to
    int max_row_0;
    int max_row_1;
    int max_row_2;
    int min_row_2;

    // Initialize a Markov structure
    Markov* M = initialize_M(size);

    // Print initial matrix
    printf("Initial Matrix:\n");
    print_M(M);
    printf("\n");

    // Update 1
    update_matrix(M, 0, 1);
    print_M(M);
    printf("\n");
    

    // Update 2
    update_matrix(M, 1, 2);
    print_M(M);
    printf("\n");
    max_row_2 = max_prob_idx(M,2);
    printf("Max probability index for M[2]: %d\n",max_row_2);
    

    // Update 3
    update_matrix(M, 2, 0);
    print_M(M);
    printf("\n");
    

    // Update 4
    update_matrix(M, 0, 2);
    print_M(M);
    printf("\n");
    min_row_2 = min_prob_idx(M,2);
    printf("Min probability index for M[2]: %d\n",min_row_2);

    // Update 5
    update_matrix(M, 1, 0);
    print_M(M);
    printf("\n");
    

    // Update 6
    update_matrix(M, 2, 1);
    print_M(M);
    printf("\n");
    

    // Update 7
    update_matrix(M, 0, 1);
    print_M(M);
    printf("\n");
    

    // Update 8
    update_matrix(M, 1, 2);
    print_M(M);
    printf("\n");
    

    // Update 9
    update_matrix(M, 2, 0);
    print_M(M);
    printf("\n");
    

    // Update 10
    update_matrix(M, 0, 0);
    print_M(M);
    printf("\n");
    max_row_0 = max_prob_idx(M,0);
    printf("Max probability index for M[0]: %d\n",max_row_0);
    

    // Update 11
    update_matrix(M, 1, 1);
    print_M(M);
    printf("\n");
    

    // Update 12
    update_matrix(M, 2, 2);
    print_M(M);
    printf("\n");
    

    // Update 13
    update_matrix(M, 0, 2);
    print_M(M);
    printf("\n");
    

    // Update 14
    update_matrix(M, 1, 0);
    print_M(M);
    printf("\n");
    

    // Update 15
    update_matrix(M, 2, 1);
    print_M(M);
    printf("\n");
    max_row_0 = max_prob_idx(M,0);
    max_row_1 = max_prob_idx(M,1);
    max_row_2 = max_prob_idx(M,2);
    printf("Max probability index for M[0]: %d\n",max_row_0);
    printf("Max probability index for M[1]: %d\n",max_row_1);
    printf("Max probability index for M[2]: %d\n",max_row_2);
    

    // Get M^2
    printf("Raising matrix to power %d...\n", power);
    Markov* result = matrix_mult(M, M);

    // Print the resulting matrix
    printf("Matrix Raised to Power %d:\n", power);
    print_M(result);

    // Free memory
    free_M(M);
    M = NULL;
    free_M(result);
    result = NULL;

    return 0;
}