/*
	Blatt02 Aufgabe2
	Heidmann
	Kornblueh
	Krabbe
*/


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

	//Setup first element to print
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
	/*
		if the start of queue is reached and there is more to print
		then print the last at before start and set index to the end
		of the queue
	*/
		if(elementToPrintIndex == 0 && elementsLeftToPrint != 1)
		{
			printf("%d  ", q -> queuespace[elementToPrintIndex]);
			elementToPrintIndex = q -> queuesize - 1;
			elementsLeftToPrint--;
		}
		printf("%d ", q -> queuespace[elementToPrintIndex]);
		elementToPrintIndex--;
	}
	puts("");
}

void queue_delete(Queue *q)
{
	free(q->queuespace);
	free(q);
}


