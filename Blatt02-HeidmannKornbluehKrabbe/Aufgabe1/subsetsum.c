#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "binarySearchSmallerK.h"

bool subsetsum(unsigned long k,
        bool *mark,
        const unsigned long *arr,
        unsigned long n)
{
    unsigned long startIndex;
    unsigned long index;
    unsigned long rest = k;
    if(!binarySearchFirstSmallerK(arr,k,n,&startIndex))
    {
    	
    	return false;
    }
    if(k == arr[startIndex + 1])
    	{
    		mark[startIndex + 1] = 1;
    		return true;
    	}
    else    	
    {	
    	index = startIndex;
    	while(rest != 0)
    	{
    		if(!binarySearchFirstSmallerK(arr,rest+1,n,&index))
    		{
    			memset(mark,0,sizeof(mark[0]) * n);
    			if(startIndex == 0)
    			{
    				return false;
    			}

    			startIndex--;
				rest = k;
				index =  startIndex;  				
    		}	    		
    		rest -= arr[index];
    		mark[index] = true;
    		

    	}
    	return true;
    	
    }



    
    // nehme naechsten kleineren zu k.
    // k - ersten = rest
    // gucken ob irgend eine zahl im forderen rest des arrays mit ersten zusammen 0 ergibt
    // wenn nicht den gucke welcher naechste einen am naehesten an das ergebniss bringt
    // dann zeile 8

    // sollte das alles nicht funktionieren -> gehe auf den 2. niedrigsten und wiederhole den ganzen shit


}