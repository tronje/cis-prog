#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "enumkmers.h"

int main(int argc, char** argv)
{

	if(argc == 1)
	{
		puts("Usage: 2 arguments needed:\n    arg1 : alphabet \n    arg2 : size of word");
		return EXIT_FAILURE;
	}
	else
	{
		buildAlphabetArray(argv[1],strtol(argv[2], NULL, 10),(unsigned)strlen(argv[1]));
	}
}