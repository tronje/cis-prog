#ifndef BINARYSEARCHSMALLERK_H
#define BINARYSEARCHSMALLERK_H
#include <stdbool.h>
#include <stdio.h>
/* 
	Binary search to find the next smaller entry after <k>.
    returns true if successfull and false if not
*/
bool binarySearchFirstSmallerK(const unsigned long *arr,
                                unsigned long k,
                                unsigned long n,
                                unsigned long* index)
{
	if(arr[0] >= k) return false;

	unsigned long currentIndex = n/2;
	unsigned long size = n;
	while(size > 1)
	{
		//printf("Current: %d\n", currentIndex);
		//printf("size: %d\n", size);
		size /= 2;
		if(size % 2 != 0 && size != 1){
			size++;
			currentIndex++;	
		}
		if(arr[currentIndex] == k)
		{
			*index = currentIndex -1;
			return true;
			//puts("If1\n");
		}
		if(arr[currentIndex] > k)
		{
			currentIndex -= size ;
			//puts("IF2\n");	
		}
		else//(arr[currentIndex] < k)
		{
			currentIndex += size;
			//puts("IF3\n");	
		}
		//printf("%d\n",size );	
	}
	*index = currentIndex - 1;
	return true;


// int main()
// {
// 	unsigned long arr[50];
// 	int lol = 0;
// 	int lmao = 0;
// 	int n = 50;
// 	for(; lol< n; lol++)
// 	{
// 		if(lol == 0)
// 		{
// 			lol++;
// 		}
// 		if(lol == 21)
// 		{
// 			lol++;
// 		}
// 		if(lol == 22)
// 		{
// 			lol++;
// 		}
// 		arr[lmao] = lol;
// 		lmao++;
		
// 	}
// 	unsigned long index = 0;
// 	unsigned long testVar = 0;
// 	for(; testVar < n; testVar++)
// 	{
// 		printf("%lu\n", index);
// 		if(binarySearchFirstSmallerK(arr,testVar,n,&index)){
// 		printf("RESULT: testVar: %lu value:%lu\n",testVar, arr[index]);
// 	}
// 	else
// 	{
// 		//printf("LOL");
// 		puts("BIN NO FIND ANy\n");
// 	}
// 	}
// 	return 0;

}
#endif
