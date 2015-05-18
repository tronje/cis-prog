#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// inttypes.h doesn't actually define uint16_t...
// #include <inttypes.h>
// stdint.h does, though:
#include <stdint.h>

#include "intset.h"
#include "checkalloc.h"

static const unsigned int d = 65536; // 2^16

/* The <IntSet> class, used to store sorted integer sets. */
struct IntSet {
    unsigned long maxvalue;
    unsigned long nofelements;
    unsigned long capacity;
    uint16_t * elements; // residual values
    unsigned long * sectionstart;
};

/* Return a new <IntSet> Object with space allocated for <nofelements> elements
   [0,<maxvalue>] */
IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements) {
    // sets contain only unique elements
    assert(nofelements <= maxvalue);

    IntSet * ret;
    ret = malloc(sizeof(IntSet));
    CHECK(ret);

    ret->sectionstart = malloc(sizeof(unsigned long)
            * (maxvalue/d+1));
    CHECK(ret->sectionstart);

    ret->elements = malloc(sizeof(uint16_t) * nofelements);
    CHECK(ret->elements);

    ret->sectionstart[0] = 0;
    ret->maxvalue = maxvalue;
    ret->capacity = nofelements;
    ret->nofelements = 0;

    return ret;
}

/* Returns the size needed to store <nofelements> integers smaller equal
   <maxvalue> */
size_t intset_size(unsigned long maxvalue, unsigned long nofelements) {
    return (sizeof(IntSet) + (maxvalue/d+1) * sizeof(unsigned long)
            + nofelements * sizeof(uint16_t));
}

/* Free the memory of <intset> */
void intset_delete(IntSet *intset) {
    // a simple if-clause might be smarter, because
    // then the program won't terminate if a non-existent
    // intset is given.
    assert(intset != NULL);
    free(intset->elements);
    free(intset->sectionstart);
    free(intset);
}

/* Add <elem> to <intset>. Fails if <elem> is larger <maxvalue> or <intset>
   already contains <nofelements> elements. */
void intset_add(IntSet *intset, unsigned long elem) {
    assert(elem <= intset->maxvalue);
    assert(intset->nofelements < intset->capacity);
    if (intset->nofelements > 0)
        assert(elem > intset->elements[intset->nofelements - 1]);
}

/* True if <elem> is stored in <intset> */
bool intset_is_member(const IntSet *intset, unsigned long elem) {

}

/* Return the index/number (0 based) of the smallest element that is larger then
   <value> from <intset> or <nofelements> if there is no such element.
   Fails if <pos> is member of <intset> */
unsigned long intset_number_next_larger(const IntSet *intset,
                                        unsigned long pos)
{

}

/* Print out the <intset> to stdout */
void intset_pretty(const IntSet *intset) {

}
