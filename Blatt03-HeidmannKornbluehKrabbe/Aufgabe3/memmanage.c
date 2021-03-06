/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */

#include "memmanage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct MMspaceblock {
    void *block;
    unsigned long size;
    unsigned long number;
    unsigned long line;
    char *file;
};

struct MMspacetable {
    unsigned long number;
    MMspaceblock *blocks;
};

void enlarge_table(MMspacetable *st) {
    unsigned long i;

    // we'll just double the table's size. Why not?
    st->blocks = (MMspaceblock*) realloc(st->blocks,
            st->number * 2 * sizeof(MMspaceblock));
    st->number = st->number * 2;

    // initialize new entries
    for (i = st->number/2; i < st->number; i++) {
        st->blocks[i].block = NULL;
        st->blocks[i].size = 0;
        st->blocks[i].number = 0;
    }
}

unsigned long get_index(MMspacetable *st, char *file, unsigned long line,
        void *ptr) {

    unsigned long i;

    // iterate over all elements
    for (i = 0; i < st->number; i++) {
        // if we find what we're looking for,
        // we can return. If not, note that
        // i now has the value of st's capacity
        if (ptr == st->blocks[i].block)
            return i;
    }

    // if the element wasn't included, and also isn't a null pointer,
    // something went wrong
    if (ptr != NULL) {
        fprintf(stderr, "Invalid pointer! %s line %lu\n", file, line);
        exit(EXIT_FAILURE);
    }

    // the block we were looking for isn't in the table
    // so we need to enlarge it
    enlarge_table(st);

    // i is still st's previous capacity,
    // therefore the first free index of st
    return i;
}


MMspacetable* mem_man_new(unsigned long numberofblocks) {
    unsigned long i;
    MMspacetable *st;

    // allocate space for a MMspacetable
    st = (MMspacetable*) malloc(sizeof(*st));

    // inside our spacetable, allocate memory for as many blocks as needed
    st->blocks = (MMspaceblock*) malloc(numberofblocks * sizeof(MMspaceblock));

    // can't forget to save the number of blocks we have
    st->number = numberofblocks;

    // initiate all blocks
    for (i = 0; i < st->number; i++) {
        st->blocks[i].block = NULL;
    }
    return st;
}

void *mem_man_alloc(MMspacetable *st, char *file, unsigned long line,
        void *ptr, unsigned long size, unsigned long number) {

    // get the index at which to alloc stuff,
    // using our handy-dandy function
    unsigned long i = get_index(st, file, line, ptr);

    // allocate accordingly
    st->blocks[i].block = realloc(ptr, size * number);

    // set all the attributes
    st->blocks[i].number = number;
    st->blocks[i].size = size;
    st->blocks[i].file = file;
    st->blocks[i].line = line;

    return st->blocks[i].block;
}

void mem_man_delete_ptr(MMspacetable *st, char *file, unsigned long line,
        void *ptr) {

    // find our index
    unsigned long i = get_index(st, file, line, ptr);

    free(st->blocks[i].block);
    st->blocks[i].block = NULL;
}

void mem_man_info(const MMspacetable *st) {
    unsigned long i;

    for(i = 0; i < st->number; i++)
    {
        if(st->blocks[i].block != NULL)
        {
            printf("# active block %lu: allocated in file \"%s\", line %lu\n",
                    i, st->blocks[i].file, st->blocks[i].line);
        }
    }
}

void mem_man_check(const MMspacetable *st) {
    unsigned long i;

    // simple iteration with some horrible printf-formatting
    for(i = 0; i < st->number; i++)
    {
        if(st->blocks[i].block != NULL)
        {
            fprintf(stderr, "space leak: main memory for block %lu not freed\n"
                    "%lu cells of size %lu\n"
                    "allocated: file \"%s\", line %lu\n",
                    i,
                    st->blocks[i].number,
                    st->blocks[i].size,
                    st->blocks[i].file,
                    st->blocks[i].line);
        }
    }
}
void mem_man_delete(MMspacetable *st) {
    free(st->blocks);
    free(st);
}
