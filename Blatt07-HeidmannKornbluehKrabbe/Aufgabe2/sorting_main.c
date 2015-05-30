#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "sorting.h"

#define MAXARRAYELEMENTS 1000000
#define MAXSORTVALUE 1000U
#define SEED 31415926

void print_usage() {
    fprintf(stderr,
            "Usage:\n"
            "./sorting.x k\n"
            "Where k is a positive integer "
            "less than or equal to 1.000.000\n");
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
    unsigned short fieldwidth;

    // must accept exactly one argument
    if (argc != 2) {
        print_usage();
        return EXIT_FAILURE;
    }

    // argument must be an integer adhering to the conditions
    nofelements = atoi(argv[1]);
    if (nofelements < 0 || nofelements > MAXARRAYELEMENTS) {
        print_usage();
        return EXIT_FAILURE;
    }

    // allocate memory for both arrays
    insertion_values = malloc(nofelements * sizeof(unsigned int));
    counting_values = malloc(nofelements * sizeof(unsigned int));
    if (insertion_values == NULL || counting_values == NULL) {
        perror("Error in sorting_main.c");
        return EXIT_FAILURE;
    }

    // populate the arrays
    // populate() guarantees that both arrays will be the same
    // after populating
    printf("# Erzeugung der Zufallszahlen...\n");
    populate(insertion_values, counting_values, nofelements);

    // sort the arrays
    printf("# Sortieren der Zufallszahlen mit Insertion Sort...\n");
    insertionsort(insertion_values, nofelements);
    printf("# Sortieren der Zufallszahlen mit Counting Sort...\n");
    countingsort(counting_values, nofelements);

    // check wether the arrays are sorted euqally
    printf("# Vergleich der Arrays...\n");
    for (i = 0; i < nofelements; i++) {
        if (insertion_values[i] != counting_values[i]) {
            fprintf(stderr, "# Arrays nicht identisch!\n");
            return EXIT_FAILURE;
        }
        // check wether an array is actually sorted
        // commented to make things faster and because it's unlikely
        // both algorithms will sort their array wrong in the same way
        //if (counting_values[i] < counting_values[i-1]) {
        //    fprintf(stderr, "Array not sorted properly!\n");
        //    return EXIT_FAILURE;
        //}
    }

    printf("Arrays identisch!\n");
    printf("Kleinste erzeugte Zufallszahl: %d\n", insertion_values[0]);
    printf("Groesste erzeugte Zufallszahl: %d\n",
            insertion_values[nofelements - 1]);

    printf("Dezentilverteilung:\n");
    printf("%*s | #Werte |\n", fieldwidth, "Dezentil");
    
    return EXIT_SUCCESS;
}
