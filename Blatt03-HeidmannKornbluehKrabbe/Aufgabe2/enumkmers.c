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
	
	char** finalAlphabet = malloc( finalAlphabetArrayLength * sizeof(char*));
	for(;currentCoeherentBlock < finalAlphabetArrayLength; currentCoeherentBlock++)
	{
		finalAlphabet[currentCoeherentBlock] = malloc(sizeof(char) * lengthOfWord);
	}
	currentCoeherentBlock = 0;
		
	for(;currentIteration < lengthOfWord; currentIteration++)
	{
		//printf("____Interation: %u____\n", currentIteration );
		for(;currentCoeherentBlock < pow(strLength,currentIteration + 1); currentCoeherentBlock++)
		{

			//printf("currentCoeherentBlock%u\n",currentCoeherentBlock );
			for(;currentPosInCoeherentBlock < finalAlphabetArrayLength/pow(strLength,currentIteration + 1); currentPosInCoeherentBlock++)
			{
				//printf("Position: %u %u \n",lol, currentIteration );
				finalAlphabet[currentPosInFinalArray][currentIteration] = letterPool[currentCoeherentBlock % strLength];
				//printf("Added: %c from index: %d\n",letterPool[currentCoeherentBlock % strLength],currentCoeherentBlock % strLength);
				currentPosInFinalArray ++;
			}
			currentPosInCoeherentBlock = 0;

		}
		currentPosInFinalArray = 0;
		currentCoeherentBlock = 0;
	}
	printAlphabetArray(finalAlphabet,finalAlphabetArrayLength);

}

