# include "binarySearchSmallerK.c"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
bool subsetsum(unsigned long k,
                bool *mark,
                const unsigned long *arr,
                unsigned long n)
    {
    	unsigned long rest = k;
    	unsigned long nextSmallerKIndex = binarySearchFirstSmallerK(arr,rest,n);
    	
    	while(rest != 0 && nextSmallerKIndex != 0)
    	{
    		nextSmallerKIndex = binarySearchFirstSmallerK(arr,rest,n);
    	    rest -= arr[nextSmallerKIndex];
    	    mark[nextSmallerKIndex] = 1;
    	    if(rest > k)
    	    {
    	    	rest = k;
    	    	memset(mark,0,n * sizeof(mark[0]));
    	    }
    	}

    	mark = 0;
    	printf("Smaller %lu\n",nextSmallerKIndex);
    	printf("rest %lu\n", rest);
    	// nehme naechsten kleineren zu k.
    	// k - ersten = rest
    	// gucken ob irgend eine zahl im forderen rest des arrays mit ersten zusammen 0 ergibt
    	// wenn nicht den gucke welcher naechste einen am naehesten an das ergebniss bringt
    	// dann zeile 8

    	// sollte das alles nicht funktionieren -> gehe auf den 2. niedrigsten und wiederhole den ganzen shit
    	return 0;
    }
