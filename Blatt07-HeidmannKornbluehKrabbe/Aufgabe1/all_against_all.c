#include "multiseq.h"
#include "string.h"
#include "unit_edist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
	Multiseq* multiseq;
	char* file_content;
	unsigned long file_size;
  unsigned char* sequence;
  unsigned char* info;
  unsigned long size;
  unsigned int threads;
  unsigned int k;
	FILE* pfile;



  if(argc != 4)
  {
    printf("ERROR: There are %d arguments but there should be 3\n",argc - 1);
    return EXIT_FAILURE;
  }

  threads = atoi(argv[2]);
  k = atoi(argv[1]);
  
  if(threads < 1)
  {
    printf("ERROR: number of threads cant be smaller than 1\n");
    return EXIT_FAILURE;
  }

  if(k < 1)
  {
    printf("ERROR: k cant be smaller than 1\n");
    return EXIT_FAILURE;
  }

	pfile = fopen(argv[3],"rb");
  if(pfile == NULL)
  {
    printf("ERROR: File could not be read from \"%s\"\n",argv[3]);
    return EXIT_FAILURE;
  }

  //Get filesize
	fseek(pfile,0L,SEEK_END);
	file_size = ftell(pfile);
  printf("FILESIZE: %lu\n", file_size);
	rewind(pfile);

	file_content = malloc(sizeof(char*) * file_size + 2);
	if(file_content == NULL) return EXIT_FAILURE;

  //Write the data form file into file_content
	fread(file_content,sizeof(char*),file_size,pfile);

  //TODO: get number of sequences form file. Then use it for gen_new
  multiseq =  gen_new_multiseq(175);

  //Get the first sequence
	info = (unsigned char*)strtok(file_content,">\n");
  sequence = (unsigned char*)strtok(NULL,">\n");
  size = strlen((char*)sequence);
  

  //As long as there are further unprocesses sequences
  while (info != NULL)
	{
    // add the current sequence to multiseq
 		multiseq_add_sequence(multiseq,sequence,info,size);
    //set new info for next seq
   	info = (unsigned char*)strtok (NULL,">\n");
    // if info is null there are no more sequences 				
  	if(info != NULL)
		{
    	//DEBUG//puts("=========================");
			//DEBUG//printf("%s\n",info );
      //set new sequence for next seq
  		sequence = (unsigned char*)strtok(NULL,">\n");
   		//DEBUG// printf("%s\n",sequence );
      //get the length of the string 
  		size = strlen((char*)sequence);
  		//DEBUG printf("%lu\n", size);
  	}

  		
  }
  // puts("=========================");
	// puts("=========================");
 	puts("ANOTHER TEST");
 	printf("%s\n",multiseq -> sequence_infos[3] );
 	printf("%s\n",multiseq -> sequences[3] );
 	printf("%ld\n",multiseq -> sizes_of_sequence[3] );
	//multiseq = multiseq_new();
  printf("%s\n",multiseq -> sequence_infos[50] );
  printf("%s\n",multiseq -> sequences[50] );
  printf("%lu\n",multiseq -> sizes_of_sequence[50] );
  unsigned long result = 0;
  printf("SIZE of 3: %lu\n",multiseq->sizes_of_sequence[3]);
  printf("SIZE of 2: %lu\n",multiseq->sizes_of_sequence[50]);
	result = eval_unit_edist(
	  multiseq -> sequences[3],
		multiseq -> sizes_of_sequence[3],
		multiseq -> sequences[50],
		multiseq -> sizes_of_sequence[50]
  );
	printf("==========makeresult: %lu\n",result );
	return EXIT_SUCCESS;
}