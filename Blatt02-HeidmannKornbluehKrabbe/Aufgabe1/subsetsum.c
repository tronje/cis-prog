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
}
