/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */
#include "tokenizer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void tokenizer (FILE * fp,
        TokenHandlerFunc tokenhandler,
        void * data) {

    unsigned long file_size;
    char * buffer = NULL;
    char * curr_word = NULL;
    int i, j; /* some handy iterators */
    bool is_valid;

    // all 'valid' chars, i.e. all chars that may
    // be included in what qualifies as a 'word'
    // by the task's definition.
    char * valids = "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "0123456789_";

    // a delimiter later to be used with strtok
    // can be pretty much any symbol.
    // Careful: more than one char makes strtok
    // split a string on an occurence of one of
    // those chars as opposed to an occurence
    // of the whole string.
    const char * delimiter = "$";

    assert(fp != NULL);

    // Seek end of file, thereby get filesize,
    // then seek the beginning of the file again.
    // Looks clumsy, but it works.
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // allocate some memory to read the file into
    buffer = malloc((file_size + 1) * sizeof(char*));
    assert(buffer != NULL);

    assert(fread(buffer, file_size, 1, fp) == 1);

    // first, split the input into valid words
    for (i = 0; i <= file_size; i++) {
        is_valid = false;
        // if the currently looked at char is included
        // in our valid chars, we're good
        for (j = 0; j < 64; j++) {
            if (buffer[i] == valids[j]) {
                is_valid = true;
                break;
            }
        }

        // if it's not, we'll just replace it with our delimiter
        if (!is_valid) {
            buffer[i] = '$';
        }
    }

    // read the first token
    curr_word = strtok(buffer, delimiter);

    // read all the tokens and use tokenhandler on them
    while (curr_word != NULL) {
        tokenhandler(curr_word, data);
        // NOTE: strtok is called with NULL instead of buffer
        // because that's just how it works. It looks wrong and weird,
        // but it's intentional
        curr_word = strtok(NULL, delimiter);
    }
}
