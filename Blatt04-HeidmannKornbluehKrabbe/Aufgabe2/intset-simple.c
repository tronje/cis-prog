#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "intset.h"

struct IntSet {
    unsigned long maxvalue;
    unsigned long nofelements;
    unsigned long capacity;
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
    ret->capacity = nofelements;
    ret->nofelements = 0;

    return ret;
}

size_t intset_size(unsigned long maxvalue, unsigned long nofelements) {
    // nofelements+3, because an IntSet contains three unsigned longs in
    // addition to the array of unsigned longs
    return ((nofelements+3) * sizeof(unsigned long));
}

void intset_delete(IntSet *intset) {
    assert(intset != NULL);
    free(intset->elements);
    free(intset);
}

void intset_add(IntSet *intset, unsigned long elem) {

    // make sure elem doesn't exceed the maximum allowed value
    assert(elem <= intset->maxvalue);

    // make sure elem isn't already in our intset
    assert(!intset_is_member(intset, elem));

    // make sure we have enough space
    assert(intset->nofelements < intset->capacity);

    // make sure the element is larger than any already
    // included element, as specified in the instructions
    if (intset->nofelements > 0)
        assert(elem > intset->elements[intset->nofelements - 1]);

//    if (intset->nofelements + 1 > intset->capacity) {
//        // realloc the elements to accomodate for the new member
//        intset->elements = realloc(intset->elements,
//                ( (intset->capacity * 2) * sizeof(unsigned long)));
//        assert(intset->elements != NULL);
//        intset->capacity *= 2;
//    }

    // write the new element to the highest index
    intset->elements[intset->nofelements++] = elem;
}

bool intset_is_member(const IntSet *intset, unsigned long elem) {
    unsigned long first, middle, last;

    if (intset->nofelements == 0)
        return false;

    if (elem > intset->maxvalue)
        return false;

    first = 0;
    last = intset->nofelements - 1;
    middle = (first + last) / 2;

    // simple little binary search
    while (first <= last) {
        if (intset->elements[middle] < elem) {
            if (middle == ULONG_MAX)
                return false;
            first = middle + 1;
        } else if (intset->elements[middle] == elem) {
            return true;
        } else {
            if (middle == 0)
                return false;
            last = middle - 1;
        }
        middle = (first + last) / 2;
    }
//    int i;
//    for (i = 0; i < intset->nofelements; i++) {
//        if (intset->elements[i] == elem)
//            return true;
//    }

    return false;
}

unsigned long intset_number_next_larger(const IntSet *intset,
        unsigned long value) {
    // we'll write something smart here soon enough
    return 0;
}
