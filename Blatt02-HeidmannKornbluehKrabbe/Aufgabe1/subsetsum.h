/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */

#ifndef SUBSETSUM_H
#define SUBSETSUM_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
/* Returns true if the ordered set of numbers <arr> of size <n> contains a
   subset with the sum of its members equal to <k>, returns false if no such
   subset exists. Elements in <mark> will be set to true for all members of
   <arr> that are part of said subset. 

    If k = 0, and arr does not include 0, the intended behaviour is tricky.
    One could argue that the sum of elements in an empty set would be 0,
    and therefore always return true for k = 0, but this seems silly.
    So, if k = 0, we return false.
*/
bool subsetsum(unsigned long k,
        bool *mark,
        const unsigned long *arr,
        unsigned long n);

#endif