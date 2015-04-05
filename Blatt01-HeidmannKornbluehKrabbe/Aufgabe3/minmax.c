/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {

    printf("== signed Variables ==\n");
    printf("name\tmin\tmax\n");
    printf("char\t%d\t%d\n", SCHAR_MIN, SCHAR_MAX);
    printf("short\t%d\t%d\n", SHRT_MIN, SHRT_MAX);
    printf("int\t%d\t%d\n", INT_MIN, INT_MAX);
    printf("long\t%d\t%d\n", LONG_MIN, LONG_MAX);

    printf("\n== unsigned Variables ==\n");
    printf("name\tmin\tmax\n");
    printf("char\t%d\t%d\n", 0, CHAR_MAX);
    printf("short\t%d\t%d\n", 0, USHRT_MAX);
    printf("int\t%d\t%d\n", 0, UINT_MAX);
    printf("long\t%d\t%d\n", 0, ULONG_MAX);



    return 0;
}
