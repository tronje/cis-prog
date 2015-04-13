#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

Queue *queue_new(unsigned long queuesize)
{
	if(queuesize == 0)
	{
		puts("queuesize was \n");
		exit(EXIT_FAILURE);
	}
	Queue* newQueue = malloc(sizeof(Queue));
	newQueue -> queuespace = calloc(sizeof(Queueelement), queuesize);
	newQueue -> queuesize = queuesize;
	newQueue -> no_of_elements = 0;
	newQueue -> enqueueindex = 0;
	newQueue -> dequeueindex = 0;
	return newQueue;
}

bool queue_is_empty(const Queue *q)
{
	if(q->no_of_elements == 0) return true;
	return false;
}

void queue_doubble_size(Queue *q)
{
	
	// puts("------------------------------\n resize \n Queue before:");
	// queue_print(q);
	// //puts("Memcpy");
	Queueelement* newMemorySpace = malloc(sizeof(Queueelement) *  q -> queuesize * 2);
	if(newMemorySpace == NULL)
	{
		puts("ERROR: Queuesize could not be doubbled, new memory block could not be allocated\n");
		exit(EXIT_FAILURE);
	}

	memcpy(newMemorySpace,q -> queuespace + q -> dequeueindex,
		(q -> queuesize - q -> dequeueindex) * sizeof(Queueelement));
	memcpy(newMemorySpace + q -> queuesize - q -> dequeueindex,
		q -> queuespace, q -> enqueueindex * sizeof(Queueelement));
	q -> enqueueindex = q -> queuesize - q -> dequeueindex + q -> enqueueindex;
	q -> dequeueindex = 0;
	free(q -> queuespace);
	q -> queuespace = newMemorySpace;
	q -> queuesize *= 2;
	// puts("\n resize \n Queue after:");
	// queue_print(q);
	// puts("--------------------------------");
}

void queue_enqueue(Queue *q, Queueelement elem)
{
	bool added = false;
	while(added != true)
	{
		if(!(q -> no_of_elements == q -> queuesize))
		{
			q -> queuespace[q->enqueueindex] = elem;
			q -> no_of_elements++;
			q -> enqueueindex++;
			if(q -> enqueueindex == q -> queuesize)
			{
				//puts("enqueue switch");
				q -> enqueueindex = 0;
			}
			added = true;
		}
		else
		{
			;
			queue_doubble_size(q);
		}
	}
}

Queueelement queue_dequeue(Queue *q)
{
	Queueelement result;
	if(!queue_is_empty(q))
	{
		result = q -> queuespace[q -> dequeueindex];
		q -> queuespace[q -> dequeueindex] = 0;
		q -> no_of_elements--;
		q -> dequeueindex++;
		if(q -> dequeueindex == q -> queuesize)
		{
			//puts("dequeue switch");
			q -> dequeueindex = 0;
		}
		return result;
	}
	puts("ERROR: Tried to pull from empty que\n");
	exit(EXIT_FAILURE);
}
void queue_print(const Queue *q)
{
	unsigned long elementsLeftToPrint = q -> no_of_elements;
	unsigned long elementToPrintIndex = 0;;
	//unsigned long elementsInOneRow = 0;

	// unsigned long debugIndex = 0;
	// puts("====Inline Start====");
	// for(;debugIndex < q -> queuesize; debugIndex++)
	// {
	// 	if(debugIndex == q-> enqueueindex) printf("en: ");
	// 	if(debugIndex == q-> dequeueindex) printf("de: ");
	// 	printf("%d  ", q -> queuespace[debugIndex]);
	// }
	// puts("\n====================");


	//printf("Size: %lu  NoOfElements: %lu\n",q -> queuesize, q -> no_of_elements);
	if(q -> enqueueindex == 0)
	{
		elementToPrintIndex = q -> queuesize -1;
	}
	else
	{
		elementToPrintIndex = q -> enqueueindex - 1;
	}

	
	puts("queue=");
	for(;elementsLeftToPrint > 0; elementsLeftToPrint--)
	{
		
		
		// if(elementsInOneRow == 9)
		// {
		// 	puts("");
		// 	elementsInOneRow = 0;
		// }
		
		//elementsInOneRow++;
		if(elementToPrintIndex == 0 && elementsLeftToPrint != 1)
		{
			// // //printf("IF DEBUG ");
			// if(elementsInOneRow == 9)
			// {
			// 	puts("");
			// 	elementsInOneRow = 0;
			// }
			printf("%d  ", q -> queuespace[elementToPrintIndex]);
			elementToPrintIndex = q -> queuesize - 1;
			elementsLeftToPrint--;
			//elementsInOneRow++;
		}
		else
		{
			printf("%d ", q -> queuespace[elementToPrintIndex]);
			elementToPrintIndex--;
		}
		//printf("LEFT: %lu\n", elementsLeftToPrint);
	}
	puts("");
}

void queue_delete(Queue *q)
{
	free(q->queuespace);
	free(q);
}


