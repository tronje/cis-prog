/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 *
 * Eine andere Moeglichkeit, die maximalen Werte
 * der verschiedenen Datentypen zu ermitteln,
 * ist die Anzahl der Bytes entsprechende zu verrechenen
 * z.B. 2^(Anzahl Bytes) - 1
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
    printf("long\t%ld\t%ld\n", LONG_MIN, LONG_MAX);

    printf("\n== unsigned Variables ==\n");
    printf("name\tmin\tmax\n");
    printf("char\t%d\t%d\n", 0, CHAR_MAX);
    printf("short\t%d\t%d\n", 0, USHRT_MAX);
    printf("int\t%d\t%u\n", 0, UINT_MAX);
    printf("long\t%d\t%lu\n", 0, ULONG_MAX);

    printf("\n== number of bytes ==\n");
    printf("name\tbytes\n");
    printf("char\t%lu\n", sizeof(char));
    printf("short\t%lu\n", sizeof(short));
    printf("int\t%lu\n", sizeof(int));
    printf("long\t%lu\n", sizeof(long));

    return 0;
}
