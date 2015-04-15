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

    // this is clumsy, but ultimately doesn't hurt.
    // we're not checking for this elsewhere...
    if(arr[0] == k) {
        return true;
    }

    // if we can't find an element in arr that is smaller
    // than k, there exists no valid subset
    if(!binarySearchFirstSmallerK(arr,k,n,&startIndex))
    {
        return false;
    }

    if(k == arr[startIndex + 1])
    {
        mark[startIndex + 1] = 1;
        return true;
    }
    else // the non-trivial part of the calculation
    {
        index = startIndex;
        while(rest != 0)
        {
            if(!binarySearchFirstSmallerK(arr,rest+1,n,&index))
            {
                // reset mark
                memset(mark,0,sizeof(mark[0]) * n);
                if(startIndex == 0)
                {
                    // we've run out of indeces
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
