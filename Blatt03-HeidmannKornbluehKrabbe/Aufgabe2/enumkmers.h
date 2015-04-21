#ifndef ENUMKMERS_H
#define ENUMKMERS_H

#include "enumkmers.c"

void buildAlphabetArray(char* letterPool, unsigned lengthOfWord, unsigned strLength);
void printAlphabetArray(char** array, unsigned arrayLength);

#endif