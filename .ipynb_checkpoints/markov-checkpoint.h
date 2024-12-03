///////////////////////////////////////////////////////////////////////////////
// markov.h
///////////////////////////////////////////////////////////////////////////////
// Author:  Seth Ely
// Date:    11/24/2024
///////////////////////////////////////////////////////////////////////////////
// Description:
//   Header file for the markov.c markov chain implementation. This
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
//   Include this header by using #include "markov.h" and use the functions
//   below
//
// NOTE:
//   The caller is responsible for freeing the allocated memory for the Markov
//   matrix (see the function "free_M" below)
///////////////////////////////////////////////////////////////////////////////

#ifndef MARKOV
#define MARKOV

#include <stdio.h>
#include <stdlib.h>

// The Markov structure contains the probability matrix, the helper array
// to keep track of the number of updates for each row, and the size as an
// attribute
typedef struct Markov {
    double** matrix; // 2D array for Markov Chain matrix
    int* helper;     // 1D array to track the number of updates to each row
    int size;        // The size of the matrix (Markov matrix will be size x size)
} Markov;

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
Markov* initialize_M(int size);

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
int update_matrix(Markov* M, int i, int j);

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
int max_prob_idx(Markov* M, int i);

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
int min_prob_idx(Markov* M, int i);

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
Markov* matrix_mult(Markov* M1, Markov* M2);

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
void free_M(Markov* M);

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
void print_M(Markov* M);

#endif