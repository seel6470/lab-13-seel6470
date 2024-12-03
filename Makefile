###############################################################################
# Makefile for Lab 13 - Markov Chain
###############################################################################
# Author: Seth Ely
# Date: 11/24/2024
###############################################################################
# Description:
#   Compiles and manages the implementation for lab 13 in a test program that
#   demonstrates the functionality of the Markov data structure implementation
#
#   Usage:
#      - make: Compiles the Markov test program
#      - make clean: Cleans up all build files and output files
#
###############################################################################

# Default build target to compile all programs
ALL: test_markov
    
# Compile the main test_markov program
test_markov: test_markov.c markov.c
	gcc -g -o test_markov test_markov.c markov.c

# Clean up all generated files
clean:
	rm -f test_markov *.o
    
# Run the test_api program using valgrind to check for memory leaks
valgrind: test_markov
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_markov
