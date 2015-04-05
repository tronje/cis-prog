/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */

#include <stdio.h>

#define MIN 0
#define MAX 100

int main(void) {
    int celsius;
    float result;

    for (celsius = MIN; celsius <= MAX; celsius++) {
        result = celsius * 9.0 / 5.0 + 32.0;
        printf("%dC is %3.1fF\n", celsius, result);
    }

    return 0;
}
