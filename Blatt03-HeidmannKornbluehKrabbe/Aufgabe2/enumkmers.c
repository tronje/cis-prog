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

