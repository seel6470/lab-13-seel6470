# Lab 13 - Markov Chain Implementation

## About

For this lab, I chose to implement a Markov Chain that could be used with the PA4 Paging assignment. To do this, I created a struct for the Markov chain named of type `Markov*` that contains the following attributes:

```
typedef struct Markov {
    double** matrix; // 2D array for Markov Chain matrix
    int* helper;     // 1D array to track the number of updates to each row
    int size;        // The size of the matrix (Markov matrix will be size x size)
} Markov;
```

## double** matrix

This represents the 2D array where each index $(i, j)$ represents the probability of a transition from state $i$ to state $j$. For the sake of a simple implementation, I have chosen to initialize this matrix to 0. While this does break the definition of a Markov chain (since rows will not initially sum to 1), each row is fixed after a single update (see the section on updating the matrix).

## int* helper

The helper array will be the size of the rows of the matrix. This array is used to keep track of the total number of updates to any row, which is a factor in creating the calculations for each update to the matrix.

## Updating the Matrix

The Matrix is updated each time a transition occurs by taking the index for the transition $(i, j)$ and updating row $i$ to increment column $j$ and normalize the values by dividing by the number of times the row has been updated. Here is an example with a newly initialized matrix:

|  |  |  |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 0 | 0 |
| 0 | 0 | 0 |

When transition is made (say from state 0 to state 2) we update the appropriate index by multiplying the row by the number of updates (initially 0) and incrementing the index at (0, 2) to get the following:

|  |  |  |
| --- | --- | --- |
| 0 | 0 | 1 |
| 0 | 0 | 0 |
| 0 | 0 | 0 |

We then increment the number of updates to now be 1 and divide by our new scale factor of 1 to get the same values. With the first update, the row will sum to 1 and represent a valid Markov chain.

From here, subsequent updates will be made the same way. Let's say we have the following Markov chain:

|  |  |  |
| --- | --- | --- |
| 0 | 0.5 | 0.5 |
| 1 | 0 | 0 |
| 0 | 1 | 0 |

This could represent a state transition in the following possible order: `0 -> 2 -> 1 -> 0 -> 1 -> 1 -> 0`

From here, let's say an update occurs from state `0 -> 1`

To update, we will follow the following steps:

- capture the value in the helper function for the number of times this row has been updated (`M->helper[0]` currently equals 1). 

- Scale all values in the appropriate row by this value. For this scenario, we multiply the first row by 2 to get the following values: $2*[ 0, 0.5,  0.5 ] = [ 0, 1,  1 ]$

- Increment the appropriate index to indicate the state change (from i to j). For this example, $M[0][1]$ increments so that our current row is $[ 0, 2,  1 ]$

- Increment `M->helper` so that it reflects the new update to the current row. For the example, `M->helper[0]` now equals 3 (since three updates have been made)

- Finally, we normalize the row by dividing by this new value. For the example, we divide all values by 3 to get $[ 0, 0.66,  0.33 ]$

The newly updated matrix after this update is now the following:

|  |  |  |
| --- | --- | --- |
| 0 | 0.66 | 0.33 |
| 1 | 0 | 0 |
| 0 | 1 | 0 |

## Additional Methods

The implementation also includes the following methods that can be used with the `Markov*` structure:

__Initialize_M(int size)__

Initializes a new Markov structure with a given matrix size, dynamically allocating memory for the 2D matrix, as well as each row of the matrix

__max_prob_idx(Markov* M, int i)__

Finds the index of the maximum probability in row `i` of the Markov matrix.

__min_prob_idx(Markov* M, int i)__

Finds the index of the minimum probability in row `i` of the Markov matrix.

__matrix_mult(Markov* M1, Markov* M2)__

Multiplies two Markov transition matrices.

__free_M(Markov* M)__

Frees the memory allocated for the Markov structure.

__print_M(Markov* M)__

Iterates through each row and prints the contents of each cell of the matrix
