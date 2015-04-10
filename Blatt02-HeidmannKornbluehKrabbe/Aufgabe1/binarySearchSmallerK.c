//#include <stdio.h>
//#include <string.h>

unsigned long binarySearchFirstSmallerK(const unsigned long *arr, unsigned long k,unsigned long n)
{
	if(arr[0] >= k) return 0;

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
			return currentIndex - 1;
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
	return currentIndex -1 ;

}

// int main()
// {
// 	unsigned long arr[50];
// 	int lol = 0;
// 	int lmao = 0;
// 	int n = 50;
// 	for(lol; lol< n; lol++)
// 	{
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
	
// 	unsigned long testArr[50];
// 	unsigned long testVar = 0;
// 	for(testVar; testVar < n; testVar++)
// 	{
// 		testArr[testVar] = binarySearchFirstSmallerK(arr,testVar,n);
// 		printf("RESULT: index: %d posNumber:%d\n",testVar, testArr[testVar]);
// 	}

// }