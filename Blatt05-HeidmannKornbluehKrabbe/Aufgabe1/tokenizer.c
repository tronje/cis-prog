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
    int i, j;
    bool is_valid;

    char * valids = "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "0123456789_";

    const char * delimiter = "$";

    assert(fp != NULL);

    // Seek end of file, thereby get filesize,
    // then seek the beginning of the file again.
    // Looks clumsy, but it works.
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    buffer = malloc((file_size + 1) * sizeof(char*));
    assert(buffer != NULL);

    assert(fread(buffer, file_size, 1, fp) == 1);

    for (i = 0; i <= file_size; i++) {
        is_valid = false;
        for (j = 0; j < 64; j++) {
            if (buffer[i] == valids[j]) {
                is_valid = true;
                break;
            }
        }

        if (!is_valid) {
            buffer[i] = 36;
        }
    }

    curr_word = strtok(buffer, delimiter);

    while (curr_word != NULL) {
        tokenhandler(curr_word, data);
        curr_word = strtok(NULL, delimiter);
    }
}
