/*
 * Heidmann
 * Kornblueh
 * Krabbe
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

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
    short offset = 0;
    unsigned int * deciles = NULL;
    const unsigned int d = MAXSORTVALUE / 10;

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

    // allocate memory for deciles array
    deciles = calloc(10, sizeof(unsigned int));
    if (deciles == NULL) {
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
    sleep(1); // countingsort() was suspiciously fast...
              // Turns out, the printf statement was called after
              // it's completion for some reason. Hence the sleep(1)
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

    fieldwidth = (int) log10(nofelements);
    if (fieldwidth < 5)
        fieldwidth = 5;

    if (MAXSORTVALUE > 1000) {
        offset = 1;
    }
    else if (MAXSORTVALUE < 1000) {
        offset = -1;
    }

    // super ugly :( :( :(
    for (i = 0; i < nofelements; i++) {
        if (insertion_values[i] <= 1 * d)
            deciles[0]++;
        else if (insertion_values[i] <= 2 * d)
            deciles[1]++;
        else if (insertion_values[i] <= 3 * d)
            deciles[2]++;
        else if (insertion_values[i] <= 4 * d)
            deciles[3]++;
        else if (insertion_values[i] <= 5 * d)
            deciles[4]++;
        else if (insertion_values[i] <= 6 * d)
            deciles[5]++;
        else if (insertion_values[i] <= 7 * d)
            deciles[6]++;
        else if (insertion_values[i] <= 8 * d)
            deciles[7]++;
        else if (insertion_values[i] <= 9 * d)
            deciles[8]++;
        else if (insertion_values[i] <= 10 * d)
            deciles[9]++;
    }

    // please never make us do something like this again
    printf("Dezentilverteilung:\n");
    printf("%*s | %*s |\n", 2 * fieldwidth - 1 + offset, "Dezentil", fieldwidth, "#Werte");
    printf("%.*s+%.*s+\n", 2 * fieldwidth + offset, "-----------------------------", fieldwidth + 3, "--------------------");
    printf("%*d-%u | %*u |\n", fieldwidth, 0, d, fieldwidth + 1, deciles[0]);
    printf("%*u-%u | %*u |\n", fieldwidth, d + 1, 2 * d, fieldwidth + 1, deciles[1]);
    printf("%*u-%u | %*u |\n", fieldwidth, 2 * d + 1, 3 * d, fieldwidth + 1, deciles[2]);
    printf("%*u-%u | %*u |\n", fieldwidth, 3 * d + 1, 4 * d, fieldwidth + 1, deciles[3]);
    printf("%*u-%u | %*u |\n", fieldwidth, 4 * d + 1, 5 * d, fieldwidth + 1, deciles[4]);
    printf("%*u-%u | %*u |\n", fieldwidth, 5 * d + 1, 6 * d, fieldwidth + 1, deciles[5]);
    printf("%*u-%u | %*u |\n", fieldwidth, 6 * d + 1, 7 * d, fieldwidth + 1, deciles[6]);
    printf("%*u-%u | %*u |\n", fieldwidth, 7 * d + 1, 8 * d, fieldwidth + 1, deciles[7]);
    printf("%*u-%u | %*u |\n", fieldwidth, 8 * d + 1, 9 * d, fieldwidth + 1, deciles[8]);
    printf("%*u-%u | %*u |\n", fieldwidth - 1, 9 * d + 1, 10 * d, fieldwidth + 1, deciles[9]);
    
    free(insertion_values);
    free(counting_values);
    free(deciles);
    return EXIT_SUCCESS;
}
