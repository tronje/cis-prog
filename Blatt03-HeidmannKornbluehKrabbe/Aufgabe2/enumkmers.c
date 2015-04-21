<<<<<<< HEAD
/*
Krabbe
Kornblueh
Heidmann
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "malloc2d.h"

void usage()
{
  printf("invalide usage\nenumkmers.x letters wordlength\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  if(argc != 3)
    {
      usage();
    }
  char *s = argv[1];
  char *a = malloc(sizeof a * strlen(argv[2]));
  char **out; 
  int lenabc = strlen(s);
  int wordlen;
  
  if(sscanf(argv[2], "%d%s", &wordlen, a)!=1)
    {
      usage();
    }
  free(a);
  
  malloc2d(out, (int) pow(lenabc, wordlen), wordlen+1);
  
  for(int i = 1; i <= wordlen; i++)
    {
      int cycle = (int)pow(lenabc, i);
      int num = (int)pow(lenabc, (wordlen - (i-1))-1);
      
      for(int j = 0; j < cycle; j++)
	{
	  for(int k = 0; k < num ; k++)
	    {
	      out[j*num + k][i-1] = s[j%lenabc];
	    }
	}
    }
  for(int i = 0; i < (int) pow(lenabc, wordlen); i++)
    {
      printf("%s\n", out[i]);
    }
  free2d(out);
  
}
=======
/*  
	Blatt03-Aufgabe2
	Heidmann
	Kornblueh
	Krabbe
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void printAlphabetArray(char** array, unsigned arrayLength)
{
	unsigned arrayIndex = 0;
	for(; arrayIndex < arrayLength; arrayIndex++)
	{
		printf("%s\n",array[arrayIndex]);
	}
}

void buildAlphabetArray(char* letterPool, unsigned lengthOfWord, unsigned strLength)
{
	unsigned currentCoeherentBlock = 0;
	unsigned currentPosInCoeherentBlock = 0;
	unsigned currentIteration = 0;
	unsigned currentPosInFinalArray = 0;
	unsigned finalAlphabetArrayLength = pow(strLength, lengthOfWord);
	
	//Init memory block for final array
	char** finalAlphabet = malloc( finalAlphabetArrayLength * sizeof(char*));
	for(;currentCoeherentBlock < finalAlphabetArrayLength; currentCoeherentBlock++)
	{
		finalAlphabet[currentCoeherentBlock] = malloc(sizeof(char) * lengthOfWord);
	}

	currentCoeherentBlock = 0;
	
	// as long as the words do not have the length we need
	for(;currentIteration < lengthOfWord; currentIteration++)
	{
		// for each coeherend block
		for(;currentCoeherentBlock < pow(strLength,currentIteration + 1); currentCoeherentBlock++)
		{
			//each coeherend block
			for(;
				currentPosInCoeherentBlock < finalAlphabetArrayLength/pow(strLength,currentIteration + 1);
			 currentPosInCoeherentBlock++)
			{
				//add the fitting letter at the end of each entry in the current block
				finalAlphabet[currentPosInFinalArray][currentIteration] = letterPool[currentCoeherentBlock % strLength];
				currentPosInFinalArray ++;
			}
			currentPosInCoeherentBlock = 0;
		}
		currentPosInFinalArray = 0;
		currentCoeherentBlock = 0;
	}
	printAlphabetArray(finalAlphabet,finalAlphabetArrayLength);
}

>>>>>>> 927727186886507b04c5f21f5e10b0ca98b90d92
