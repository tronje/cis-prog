/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */

#include <stdio.h>
#include <stdlib.h>

void usage(void) {
    printf("Usage: hello.x [name]\n");
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Too many parameters!\n");
        usage();
        return EXIT_FAILURE;
    } else if (argc == 1) {
        printf("Hello World\n");
        return EXIT_SUCCESS;
    }
    printf("Hello %s\n", argv[1]);
    return EXIT_SUCCESS;
}
