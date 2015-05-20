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
    unsigned long greatest;
    uint16_t * elements; // residual values
    unsigned long * sectionstart;
};

/* Return a new <IntSet> Object with space allocated for <nofelements> elements
   [0,<maxvalue>] */
IntSet *intset_new(unsigned long maxvalue, unsigned long nofelements) {
    // sets contain only unique elements
    assert(nofelements <= maxvalue);

    // allocate what we need
    IntSet * ret;
    ret = malloc(sizeof(IntSet));
    CHECK(ret);

    ret->sectionstart = malloc(sizeof(unsigned long)
            * (maxvalue/d+1));
    CHECK(ret->sectionstart);

    ret->elements = malloc(sizeof(uint16_t) * nofelements);
    CHECK(ret->elements);

    // initialize values
    ret->sectionstart[0] = 0;
    ret->maxvalue = maxvalue;
    ret->capacity = nofelements; // so unintuitive
    ret->nofelements = 0;
    ret->greatest = 0;

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
    unsigned long i;
    uint16_t r = (uint16_t) elem % d;
    unsigned long q = elem >> 16;
    unsigned long greatest = intset->greatest;
    unsigned long greatest_q = greatest >> 16;

    // typical asserts
    assert(elem <= intset->maxvalue);
    assert(intset->nofelements < intset->capacity);
    if (intset->nofelements > 0)
        assert(elem > greatest);

    // start a new section if needed
    if (q > greatest_q) {
        intset->sectionstart[q] = intset->nofelements;
        // ... and initialize it
        for (i = greatest_q + 1; i < q; i++) {
            intset->sectionstart[i] = intset->nofelements;
        }
    }

    // add stuff
    intset->elements[intset->nofelements] = r;
    intset->nofelements++;
    intset->greatest = elem;
}

// handy dandy binary search now as it's own function
static bool bin_search(const IntSet *s, unsigned long elem,
        unsigned long first, unsigned long last)
{
    unsigned long middle;
    
    while (first <= last) {
        // equivalent to (first + last)/2 but save from overflows
        middle = first + ((last - first) / 2);

        if (s->elements[middle] > elem) {
            if (middle == 0)
                return false;

            last = middle - 1;
        }
        else if(s->elements[middle] < elem) {
            if(middle >= s->capacity)
                return false;

            first = middle + 1;
        }
        else {
            return true;
        }
    }
    return false;
}

/* True if <elem> is stored in <intset> */
bool intset_is_member(const IntSet *intset, unsigned long elem) {
    uint16_t r = (uint16_t) elem % d;
    unsigned long q = elem >> 16;
    unsigned long greatest = intset->greatest;
    unsigned long greatest_q = greatest >> 16;

    if (elem > greatest) {
        return false;
    }
    else if(q == greatest_q) {
        return bin_search(
	    intset, r, intset->sectionstart[q], intset->nofelements - 1);
    }
    else {
        return bin_search(
	    intset, r, intset->sectionstart[q], intset->sectionstart[q+1] - 1);
    }
}

/* Return the index/number (0 based) of the smallest element that is larger then
   <value> from <intset> or <nofelements> if there is no such element.
   Fails if <pos> is member of <intset> */
unsigned long intset_number_next_larger(const IntSet *intset,
        unsigned long value)
{
    /*
      Due to problems with value beeing bigger than 2^16-1 (65535) we where not 
      able to finish this task
     */
    
    unsigned long middle, first, last;
    unsigned long nofelements;
    unsigned long q = value >> 16;
    unsigned long greatest = intset->greatest;
    unsigned long greatest_q = greatest >> 16;
    //value = value % d;
    if(q == greatest_q)
    {
	first = intset->sectionstart[q];
	last = intset->nofelements-1;
	nofelements = (last - first)-1;
    }
    else
    {
	first = intset->sectionstart[q];
	last = intset->sectionstart[q+1]-1;
	nofelements = (last - first)-1;
    }
    fprintf(stderr, "first : %lu last : %lu fval : %hu %hu %lu\n", first, last,
	    intset->elements[first], intset->elements[last], value);

    if(value < intset->elements[first])
    {
	return first;
    }
    
    /// assert(!intset_is_member(intset, value));
    
    
    if(value > intset->elements[last])
    {
	return last+1;
	//return intset->nofelements;
    }
    while(first < last-1)
    {
	middle = ((first + last) / 2);
	if(intset->elements[middle] > value)
	{
	    last = middle;
	}
	else
	{
	    first = middle;
	}
    }
    return last;
}

/* Print out the <intset> to stdout */
void intset_pretty(const IntSet *intset) {
    unsigned long i, q = 0;

    for (i = 0; i < intset->nofelements; i++) {
        while (q < intset->greatest / d && i == intset->sectionstart[q+1])
            q++;

        printf("[%lu] %lu\n", i, d * q + intset->elements[i]);
    }
}
