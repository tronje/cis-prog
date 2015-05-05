#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void printer(const char * token, void * data) {
    if (token == NULL)
        return;
    printf("%s\n", token);
    if (data == NULL)
        return;
}

int main(int argc, char ** argv) {
    FILE * fp = NULL;

    if (argc != 2) {
        fprintf(stderr, "Invalid arguments!\n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    assert(fp != NULL);

    tokenizer(fp, printer, NULL);
    return EXIT_SUCCESS;
}
