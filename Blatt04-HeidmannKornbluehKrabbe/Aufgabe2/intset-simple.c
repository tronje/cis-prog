#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "intset.h"

struct IntSet {
    unsigned long maxvalue;
    unsigned long nofelements;
    unsigned long *elements;
};

IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements) {
    // sets contain only unique elements
    assert(nofelements <= maxvalue);

    IntSet *ret;

    // alloc space for our IntSet
    ret = (IntSet*) malloc(sizeof(*ret));
    assert(ret != NULL);

    // alloc space for our IntSet's array of elements
    ret->elements = malloc(nofelements * sizeof(unsigned long));
    assert(ret->elements != NULL);

    // set our IntSet's attributes
    ret->maxvalue = maxvalue;
    ret->nofelements = nofelements;

    return ret;
}

size_t intset_size(unsigned long maxvalue, unsigned long nofelements) {
    // nofelements+2, because an IntSet contains two unsigned longs in
    // addition to the array of unsigned longs
    return ((nofelements+2) * sizeof(unsigned long));
}

void intset_delete(IntSet *intset) {
    free(intset->elements);
    free(intset);
}

void intset_add(IntSet *intset, unsigned long elem) {
    unsigned long i;
    i = intset->nofelements;

    // make sure elem doesn't exceed the maximum allowed value
    assert(elem < intset->maxvalue);

    // make sure elem isn't already in our intset
    assert(!intset_is_member(intset, elem));

    // realloc the elements to accomodate for the new member
    intset->elements = realloc(intset->elements,
            ( (i + 1) * sizeof(unsigned long)));
    assert(intset->elements != NULL);

    // write the new element to the highest index
    // note that index i would have been invalid (as indeces start at 0)
    // but we realloced our array, so now i is the max index, and i+1
    // is the number of members
    intset->elements[i] = elem;

    // adjust variable holding the number of elements in the intset
    intset->nofelements++;
}

bool intset_is_member(const IntSet *intset, unsigned long elem) {
    if (elem > intset->maxvalue)
        return false;

    // for efficiency's sake, we've declared our variables here,
    // and not at the top of the function, because we can save
    // the time should the if-clause catch something!
    // we hope to be excused!
    unsigned long first, middle, last;

    first = 0;
    last = intset->nofelements - 1;
    middle = (first + last) / 2;

    // simple little binary search
    while (first <= last) {
        if (intset->elements[middle] < elem) {
            first = middle + 1;
        } else if (intset->elements[middle] == elem) {
            return true;
        } else {
            last = middle - 1;
        }
        middle = (first + last)/2;
    }

    return false;
}

unsigned long intset_number_next_larger(const IntSet *intset,
        unsigned long value) {
    // we'll write something smart here soon enough
    return 0;
}
