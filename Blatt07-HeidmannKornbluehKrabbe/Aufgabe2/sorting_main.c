#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "sorting.h"

#define MAXARRAYELEMENTS 1000000
#define MAXSORTVALUE 1000U
#define SEED 31415926

void print_usage() {
    fprintf(stderr, "Usage:\n./sorting.x k\n"
                    "Where k is a positive integer"
                    " smaller than 1 000 000\n");
}

void populate(unsigned int * insertion_values,
              unsigned int * counting_values,
              unsigned long nofelements)
{
    int i;
    srand48(SEED);
    for (i = 0; i < nofelements; i++) {
        insertion_values[i] = counting_values[i] =
            (unsigned int) (drand48() * (MAXSORTVALUE+1));
    }
}

int main(int argc, char ** argv) {
    unsigned long nofelements, i;
    unsigned int * insertion_values = NULL;
    unsigned int * counting_values = NULL;

    if (argc != 2) {
        print_usage();
        return EXIT_FAILURE;
    }

    nofelements = atoi(argv[1]);
    if (nofelements < 0 || nofelements > MAXARRAYELEMENTS) {
        print_usage();
        return EXIT_FAILURE;
    }

    insertion_values = malloc(nofelements * sizeof(unsigned int));
    counting_values = malloc(nofelements * sizeof(unsigned int));
    if (insertion_values == NULL || counting_values == NULL) {
        perror("Error in sorting_main.c");
        return EXIT_FAILURE;
    }

    populate(insertion_values, counting_values, nofelements);

    insertionsort(insertion_values, nofelements);
    countingsort(counting_values, nofelements);

    for (i = 0; i < nofelements; i++) {
        if (insertion_values[i] != counting_values[i]) {
            fprintf(stderr, "Arrays aren't equal after sorting!\n");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
