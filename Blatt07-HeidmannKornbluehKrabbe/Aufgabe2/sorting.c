/*
 * Heidmann
 * Kornblueh
 * Krabbe
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#include "sorting.h"

void insertionsort(unsigned int *values, unsigned long nofelements) {
    unsigned long i, j, k;

    for (i = 0; i < nofelements; i++) {
        j = i;

        while (j > 0 && values[j - 1] > values[j]) {
            k = values[j];
            values[j] = values[j - 1];
            values[j - 1] = k;
            j--;
        }
    }
}

void countingsort(unsigned int *values, unsigned long nofelements) {
    // k should be equal to the largest element in values.
    // Unfortunately, we can't be sure of this value.
    // We could, since we first sort with insertion sort,
    // pass this value to counting sort, but then counting sort
    // could not be called individually. Using UINT_MAX
    // the memory allocation fails on my machine, as I imagine
    // it will on others. The solution is to use the same value as defined
    // in the macro in sorting_main, and to hope it will remain unchanged.
    unsigned int k = 1000000;//UINT_MAX;
    unsigned int * count = NULL;
    unsigned int * output = NULL; // we're not very space efficient
    unsigned int i, old_count, total;

    // allocate count variable and initialize with zeroes
    count = calloc(k, sizeof(unsigned long));
    if (count == NULL) {
        perror("Error in sorting.c");
        exit(EXIT_FAILURE);
    }

    // allocate output array
    output = malloc(sizeof(unsigned int) * nofelements);
    if (output == NULL) {
        perror("Error in sorting.c");
        exit(EXIT_FAILURE);
    }

    // count number of occurences of every value in *values
    // this is why it's called counting sort
    for (i = 0; i < nofelements; i++) {
        count[values[i]] += 1;
    }

    total = 0;
    for (i = 0; i < k; i++) {
        old_count = count[i];
        count[i] = total;
        total += old_count;
    }

    for (i = 0; i < nofelements; i++) {
        output[count[values[i]]] = values[i];
        count[values[i]] += 1;
    }

    // overwrite the initial array with the sorted array
    memcpy(values, output, sizeof(unsigned int) * nofelements);
    free(count);
    free(output);
}
