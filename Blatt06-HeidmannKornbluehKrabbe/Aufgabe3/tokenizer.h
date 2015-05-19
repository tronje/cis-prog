/*
 * Oliver Heidmann
 * Jorim Kornblueh
 * Tronje Krabbe
 */
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>

typedef void (*TokenHandlerFunc)(const char *, void *);
void tokenizer(FILE * fp, TokenHandlerFunc tokenhandler, void * data);

#endif
