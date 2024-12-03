///////////////////////////////////////////////////////////////////////////////
// markov.c
///////////////////////////////////////////////////////////////////////////////
// Author:  Seth Ely
// Date:    11/24/2024
///////////////////////////////////////////////////////////////////////////////
// Description:
//   Contains the implementation of a markov chain as a data structure. This
//   implementation was specifically designed with the programming assignment 4
//   in mind. In the event of a state change, the rows represent the previous 
//   state and the columns represent the transition state. Each cell represents
//   the probability of the previous state moving to the transitionary state,
//   with all columns adding to 1.
//   
//   Functions include initialization, updating the matrix based on state
//   transitions, matrix multiplication, freeing memory, and printing the matrix
//
// Usage:
//   Include this source code by using #include "markov.h" and use the functions
//   below
//
// NOTE:
//   The caller is responsible for freeing the allocated memory for the Markov
//   matrix (see the function "free_M" below)
//
//   Additionally, a Markov Chain should always sum to 1, however for the sake
//   of simplicity, all indices in the matrix are initialized to 0. In this
//   circumstance, the probabilies of state change from i to j will be equal 
//   (albeit 0) and the most probabilistic outcome can be computed the same.
//   As soon as an update to any row occurs, the index for the first state
//   change is equal to 1, all others being 0. This returns the correct most
//   probable state change (and least probable state changes are tied to 0).
//
//   With each additional update, the indices in each row represent the ratio
//   of each transition from state i to state j over all transitions from
//   state i.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "markov.h"

///////////////////////////////////////////////////////////////////////////////
// initialize_M(int size)
//
//  Initializes a new Markov structure with a given matrix size, dynamically
//  allocating memory for the 2D matrix, as well as each row of the matrix
//
// Parameters:
//    - size: The number of rows and columns in the transition matrix (the 
//            Markov matrix should be square)
//
// Returns:
//    Pointer to the newly allocated Markov structure
///////////////////////////////////////////////////////////////////////////////
Markov* initialize_M(int size) {
    // Step 1.
    //   Allocate memory for the Markov structure
    // Step 2.
    //   Set the size attribute of the Markov structure
    // Step 3.
    //   Allocate memory for the matrix attribute of the Markov struct
    // Step 4.
    //   Allocate memory for each row of the matrix, initializing each value to 0
    // Step 5.
    //   Allocate memory for the helper integer array, initializing each value to 0
    //   This array is used to keep track of how many times each row has been
    //   updated in the matrix, which is important for the arithmetic that
    //   calculates the new values for a row given a state change from row i to 
    //   column j (see "update_matrix" for more info on this)
    
    Markov* M = (Markov*)malloc(sizeof(Markov));
    if (M == NULL) {
        perror("Failed to allocate memory for Markov structure");
        exit(EXIT_FAILURE);
    }
    
    // set the size
    M->size = size;

    // Allocate memory for the matrix (2D array)
    M->matrix = (double**)malloc(size * sizeof(double*));
    if (M->matrix == NULL) {
        perror("Failed to allocate memory for matrix");
        free(M);
        exit(EXIT_FAILURE);
    }
    // Allocate memory for each row of the matrix
    for (int i = 0; i < size; i++) {
        M->matrix[i] = (double*)calloc(size, sizeof(double)); // Initialize to 0.0
        if (M->matrix[i] == NULL) {
            perror("Failed to allocate memory for matrix row");
            for (int j = 0; j < i; j++) {
                free(M->matrix[j]);
            }
            free(M->matrix);
            free(M);
            exit(EXIT_FAILURE);
        }
    }

    // Allocate memory for the helper array
    M->helper = (int*)calloc(size, sizeof(int)); // Initialize to 0
    if (M->helper == NULL) {
        perror("Failed to allocate memory for helper array");
        for (int i = 0; i < size; i++) {
            free(M->matrix[i]);
        }
        free(M->matrix);
        free(M);
        exit(EXIT_FAILURE);
    }

    return M;
}

///////////////////////////////////////////////////////////////////////////////
// update_matrix(Markov* M, int i, int j)
//
//  Updates the transition matrix to reflect a state transition from prevcious 
//  state (row) i to the next state (column) j
//
// Parameters:
//    - M: (Markov*) pointer to the Markov structure
//    - i: (int) index of the previous state (row)
//    - j: (int) index of the next state (column)
//
// Returns:
//    - 0 on success, -1 for invalid parameters
///////////////////////////////////////////////////////////////////////////////
int update_matrix(Markov* M, int i, int j) {
    // Step 1.
    //   Check that the indices i and j are valid
    // Step 2.
    //   capture the value in the helper array that represents the total number
    //   of times this row has been updated before incrementing it.
    // Step 3.
    //   Iterate through each index in the row, multiplying the value by the 
    //   number of times it has been updated (alpha). This will change the values 
    //   of each cell to represent the total number of transitions from state i 
    //   to state j instead of the probabilities of transitioning from state i to
    //   state j.
    // Step 4.
    //   Increment the value representing the transition from state i to state j 
    //   ( Matrix[i][j] )
    // Step 5.
    //   Divide by the new number of updates (alpha + 1) to create the change the
    //   cell values back to probability values
    
    // Check for incorrect indices
    if (i >= M->size || j >= M->size || i < 0 || j < 0) {
        fprintf(stderr, "invalid i, j indices ( %d, %d ) given size of %d.\n",i,j,M->size);
        return -1;
    }
    
    // capture the current number of updates to the row in alpha before incrementing
    // this value in the helper array
    int alpha = M->helper[i]++;   
    
    // multiply by the number of updates to have each cell represent the total
    // number of transitions from state i to state j (instead of probabilities)
    for (int k = 0; k < M->size; k++) {
        M->matrix[i][k] *= alpha;
        // Increment the index representing the state change indicated by the
        // i, j parameters (transition from state i to state j)
        if (k == j) {
            M->matrix[i][k]++;
        }
        // divide by the new number of updates to have each index in the row
        // represent probabily of moving from state i to state j
        M->matrix[i][k] = M->matrix[i][k] / (alpha + 1);
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// max_prob_idx(Markov* M, int i)
//
//  Finds the index of the maximum probability in row `i` of the Markov matrix.
//
// Parameters:
//    - M: Pointer to the Markov structure.
//    - i: Index of the row to search.
//
// Returns:
//    - The column index of the maximum probability in the row.
//    - -1 if the input is invalid or the row index is out of bounds.
//
// NOTE:
//    Returns the leftmost index in the event of a tie
///////////////////////////////////////////////////////////////////////////////
int max_prob_idx(Markov* M, int i) {
    if (M == NULL || M->matrix == NULL || i < 0 || i >= M->size) {
        fprintf(stderr, "Invalid input or row index out of bounds.\n");
        return -1; // Return an error indicator
    }

    int max_idx = 0; // Assume the first column has the max probability
    double max_val = M->matrix[i][0];

    for (int j = 1; j < M->size; j++) {
        if (M->matrix[i][j] > max_val) {
            max_val = M->matrix[i][j];
            max_idx = j;
        }
    }

    return max_idx;
}


///////////////////////////////////////////////////////////////////////////////
// min_prob_idx(Markov* M, int i)
//
//  Finds the index of the minimum probability in row `i` of the Markov matrix.
//
// Parameters:
//    - M: Pointer to the Markov structure.
//    - i: Index of the row to search.
//
// Returns:
//    - The column index of the minimum probability in the row
//    - -1 if the input is invalid or the row index is out of bounds
//
// NOTE:
//    Returns the leftmost index in the event of a tie
///////////////////////////////////////////////////////////////////////////////
int min_prob_idx(Markov* M, int i) {
    if (M == NULL || M->matrix == NULL || i < 0 || i >= M->size) {
        fprintf(stderr, "Invalid input or row index out of bounds.\n");
        return -1; // Return an error indicator
    }

    int min_idx = 0; // Assume the first column has the min probability
    double min_val = M->matrix[i][0];

    for (int j = 1; j < M->size; j++) {
        if (M->matrix[i][j] < min_val) {
            min_val = M->matrix[i][j];
            min_idx = j;
        }
    }

    return min_idx;
}

///////////////////////////////////////////////////////////////////////////////
// matrix_mult(Markov* M1, Markov* M2)
//
//  Multiplies two Markov transition matrices.
//
// Parameters:
//    - M1: Pointer to the first Markov structure
//    - M2: Pointer to the second Markov structure
//
// Returns:
//    - A pointer to the resulting Markov structure containing the results of
//      matrix multiplication or NULL on error
///////////////////////////////////////////////////////////////////////////////
Markov* matrix_mult(Markov* M1, Markov* M2) {
    // Step 1.
    //   Check that both structures have equal sizes
    // Step 2.
    //   Initialize a new matrix to hold the return structure
    // Step 3.
    //   Iterate through each index in the matrix, calculating
    //   the appropriate dot product (row x column) for each cell, according
    //   to proper matrix multiplication
    
    if (M1->size != M2->size) {
        fprintf(stderr, "Both Markov matrices must be of equal size. %d != %d\n",M1->size,M2->size);
        return NULL;
    }
    // Initialize the resulting Markov structure with the same size
    Markov* result = initialize_M(M1->size);

    // Perform matrix multiplication
    for (int i = 0; i < M1->size; i++) {
        for (int j = 0; j < M2->size; j++) {
            // for each index (i, j) perform the dot product of M1[i] * M2[:,j]
            for (int k = 0; k < M1->size; k++) {
                result->matrix[i][j] += M1->matrix[i][k] * M2->matrix[k][j];
            }
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
// free_M(Markov* M)
//
//  Frees the memory allocated for the Markov structure.
//
// Parameters:
//    - M: Pointer to the Markov structure
//
// Returns:
//    - None
///////////////////////////////////////////////////////////////////////////////
void free_M(Markov* M) {
    if (M == NULL) return;

    // Free the matrix
    for (int i = 0; i < M->size; i++) {
        free(M->matrix[i]);
    }
    free(M->matrix);

    // Free the helper array
    free(M->helper);

    // Free the structure itself
    free(M);
}

///////////////////////////////////////////////////////////////////////////////
// print_M(Markov* M)
//
//  Iterates through each row and prints the contents of each cell of the matrix
//
// Parameters:
//    - M: Pointer to the Markov structure.
//
// Returns:
//    - None
///////////////////////////////////////////////////////////////////////////////
void print_M(Markov* M) {
    for (int i = 0; i < M->size; i++) {
        for (int j = 0; j < M->size; j++) {
            printf("%.3f ", M->matrix[i][j]);
        }
        // line-feed after each row
        printf("\n");
    }
}
