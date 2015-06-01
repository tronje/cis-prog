#include "multiseq.h"
#include "string.h"
#include "unit_edist.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Multiseq* multiseq;
	char* file_content;
	unsigned long file_size;
  unsigned char* sequence;
  unsigned char* info;
  unsigned long size;
	FILE* pfile;

	pfile = fopen("sw175.fna","r");
	fseek(pfile,0L,SEEK_END);
	file_size = ftell(pfile);
	rewind(pfile);

	file_content = malloc(sizeof(char) * file_size + 1);
	if(file_content == NULL) return EXIT_FAILURE;
	fread(file_content,sizeof(char*),file_size,pfile);

	info = (unsigned char*)strtok(file_content,">\n");
  sequence = (unsigned char*)strtok(NULL,">\n");
  size = strlen((char*)sequence);
  multiseq =  gen_new_multiseq(175);
  while (info != NULL)
	{
 		multiseq_add_sequence(multiseq,sequence,info,size);
   	info = (unsigned char*)strtok (NULL,">\n");   				
  	if(info != NULL)
		{
    	// puts("=========================");
			// printf("%s\n",info );
  		sequence = (unsigned char*)strtok(NULL,">\n");
   		// printf("%s\n",sequence );
  		size = strlen((char*)sequence);
  		// printf("%lu\n", size);
  	}

  		
  }
  // puts("=========================");
	// puts("=========================");
 	puts("ANOTHER TEST");
 	printf("%s\n",multiseq -> sequence_infos[3] );
 	printf("%s\n",multiseq -> sequences[3] );
 	printf("%ld\n",multiseq -> sizes_of_sequence[3] );
	//multiseq = multiseq_new();
  printf("%s\n",multiseq -> sequence_infos[2] );
  printf("%s\n",multiseq -> sequences[2] );
  unsigned long result = 0;
	eval_unit_edist(
	  multiseq -> sequences[3],
		multiseq -> sizes_of_sequence[3],
		multiseq -> sequences[2],
		multiseq -> sizes_of_sequence[2]
  );
	printf("==========makeresult: %lu\n",result );
	return EXIT_SUCCESS;
}