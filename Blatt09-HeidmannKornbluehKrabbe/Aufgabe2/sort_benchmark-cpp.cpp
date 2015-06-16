/*
 * Heidmann
 * Kornblueh
 * Krabbe
 */

/*
$ ./sort_benchmark-c.x
Runtime (hh:mm:ss:us)    00:00:00:069270

$ ./sort_benchmark-cpp.x
Runtime (hh:mm:ss:us)   00:00:10:457269

Das C++ Programm ist ca. um einen Faktor 150
langsamer, was beunruhigend ist, da C++'s std::sort()
angeblich zweimal so schnell ist wie C's qsort().
Dies liegt daran, dass qsort() immer noch eine Funktion
ruft, während der Vergleich bei std::sort() eingebaut ist.
Aber wir sehen keinen Fehler in unserem Port.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>

#define NUMVALUES (1 << 20)
/* 128 */
#define NUMSORTS (1 << 7)

static int timeval_subtract(struct timeval *result,
                            struct timeval *x,
                            struct timeval *y)
{
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;
    return x->tv_sec < y->tv_sec;
}

static int timeval_add(struct timeval *result,
                       const struct timeval *x,
                       const struct timeval *y)
{
    result->tv_sec = x->tv_sec + y->tv_sec;
    result->tv_usec = x->tv_usec + y->tv_usec;
    while (result->tv_usec > 1000000) {
        result->tv_usec -= 1000000;
        result->tv_sec++;
    }
    return 0;
}

int main(void)
{
    std::vector<int> values(NUMVALUES);
    unsigned long idx, sortnum;
    struct timeval start, end, diff, tmp, runtime = {0,0};

    for (sortnum = 0; sortnum < NUMSORTS; ++sortnum) {
        for (idx = 0; idx < NUMVALUES; ++idx) {
            values[idx] = rand();
        }
        (void) gettimeofday(&start, NULL);
        std::sort(values.begin(), values.end());
        (void) gettimeofday(&end, NULL);
        (void) timeval_subtract(&diff, &end, &start);
        tmp = runtime;
        (void) timeval_add(&runtime, &tmp, &diff);
        /* printf("Runtime (hh:mm:ss:us)\t%02lu:%02lu:%02lu:%06lu\n",
           runtime.tv_sec / 60LU / 60LU,
           (runtime.tv_sec / 60LU) % 60LU,
           runtime.tv_sec % 60LU,
           runtime.tv_usec); */
    }

    printf("Runtime (hh:mm:ss:us)\t%02lu:%02lu:%02lu:%06lu\n",
            runtime.tv_sec / 60LU / 60LU,
            (runtime.tv_sec / 60LU) % 60LU,
            runtime.tv_sec % 60LU,
            runtime.tv_usec);

    return 0;
}
