#include "tokenizer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void tokenizer (FILE * fp,
        TokenHandlerFunc tokenhandler,
        void * data) {

    unsigned long file_size;
    char ** buffer = NULL;
    char curr_char;
    int i, j, k;
    int wordcount;
    bool is_valid;

    char * valids = "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "0123456789_";

    assert(fp != NULL);

    // Seek end of file, thereby get filesize,
    // then seek the beginning of the file again.
    // Looks clumsy, but it works.
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    buffer = malloc(file_size * sizeof(char));
    assert(buffer != NULL);

    assert(fread(buffer, sizeof(char), file_size, fp) == file_size);

    wordcount = 0;
    k = 0;
    for (i = 0; i < file_size; i++) {
        is_valid = false;
        curr_char = (char) fgetc(fp);
        for (j = 0; j < 63; j++) {
            if (curr_char == valids[j]) {
                is_valid = true;
                break;
            }
        }

        if (is_valid) {
            buffer[wordcount][k] = curr_char;
            k++;
        }
        else {
            wordcount++;
            k = 0;
        }
    }

    for (i = 0; i <= wordcount; i++) {
        tokenhandler(buffer[i], data);
    }

}
