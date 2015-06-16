/*
 * Heidmann
 * Kornblueh
 * Krabbe
 */

/*
$ ./sort_benchmark-c.x
Runtime (hh:mm:ss:us)   00:00:17:528965

$ ./sort_benchmark-cpp.x
Runtime (hh:mm:ss:us)   00:00:10:457269

Das C++ Programm ist etwa 1.7 mal so schnell wie das
C Programm. Dies liegt wahrscheinlich daran, dass
std::sort keine separate Funktion aufruft, qsort
jedoch bei jedem Vergleich zweier Elemente die compare
Funktion rufen muss.
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

    for (idx = 0; idx < NUMVALUES; idx++) {
        printf("%d\n", values[idx]);
    }

    printf("Runtime (hh:mm:ss:us)\t%02lu:%02lu:%02lu:%06lu\n",
            runtime.tv_sec / 60LU / 60LU,
            (runtime.tv_sec / 60LU) % 60LU,
            runtime.tv_sec % 60LU,
            runtime.tv_usec);

    return 0;
}
