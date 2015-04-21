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

unsigned long get_block_index(MMspacetable *st, char *file, unsigned long line,
        void *ptr) {
    
    unsigned long i;

    for (i = 0; i < st->number; i++) {
        if (ptr == st->blocks[i].block)
            return i;
    }

    if (ptr != NULL)
        exit(EXIT_FAILURE);
    
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

    st->number += 1;
    st->blocks = realloc(ptr, (st->));
    st->blocks->block = realloc(ptr, (number * size));
    st->blocks->file = file;
    st->blocks->line = line;
    st->blocks->size = size;
    st->blocks->number = number;

    return &(st->blocks->block);
}

void mem_man_delete_ptr(MMspacetable *st, char *file, unsigned long line,
        void *ptr) {
    
    int i;
    for (i = 0; i < st->size; i++) {
        if (st->blocks[i]-)
    }
}
void mem_man_info(const MMspacetable *st);
void mem_man_check(const MMspacetable *st);
void mem_man_delete(MMspacetable *st);
