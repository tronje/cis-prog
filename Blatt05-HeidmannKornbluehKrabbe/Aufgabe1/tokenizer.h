#ifndef TOKENIZER_H
#define TOKENIZER_H

typdef void (*TokenHandlerFunc) (const char *, void *);
void tokenizer (FILE * fp, TokenHandlerFunc tokenhandler, void * data);

#endif
