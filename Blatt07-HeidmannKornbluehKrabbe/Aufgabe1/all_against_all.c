#include "multiseq.h"
#include "string.h"
#include "unit_edist.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char**argv)
{
    Multiseq* multiseq;
    char* file_content = NULL;
    unsigned long file_size;
    unsigned char* sequence = NULL;
    unsigned char* info = NULL;
    unsigned long size;
    unsigned long result = 0;
    unsigned int threads;
    unsigned int k;
    FILE* pfile = NULL;



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

    pfile = fopen(argv[3],"r");
    if(pfile == NULL)
    {
        printf("ERROR: File could not be read from \"%s\"\n",argv[3]);
        return EXIT_FAILURE;
    }

    //Get filesize
    fseek(pfile,0L,SEEK_END);
    file_size = ftell(pfile);
    rewind(pfile);

    file_content = malloc(sizeof(char) * (file_size + 1));
    if (file_content == NULL) {
        perror("Error in all_against_all.c");
        return EXIT_FAILURE;
    }

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
    printf("%s\n",multiseq -> sequence_infos[3]);
    printf("%s\n",multiseq -> sequences[3]);
    printf("%ld\n",multiseq -> sizes_of_sequence[3]);
    //multiseq = multiseq_new();
    printf("%s\n",multiseq -> sequence_infos[2]);
    printf("%s\n",multiseq -> sequences[2]);

    eval_unit_edist(
            multiseq -> sequences[3],
            multiseq -> sizes_of_sequence[3],
            multiseq -> sequences[2],
            multiseq -> sizes_of_sequence[2]
            );
    printf("==========makeresult: %lu\n",result );
    return EXIT_SUCCESS;
}
typedef struct pthread_range_data pthread_range_data;

struct pthread_range_data
{
    unsigned long start;
    unsigned long range;
}

void eval_seqrange(Multiseq seq)
{
    int index;
    int rest;
    int default_range;
    int next_start = 0;
    int next_end = 0;
    pthread_range_data* range_data;

    rest = n % t;
    default_range = n / t;

    for(index = 0; index < t; index++)
    {
        range_data -> start = next_start;
        if(rest > 0)
        {
            range_data -> range = default_range + 1;             
        }
        else
        {
            range_data -> range = default_range;
        }
        printf("Start of t %d: %d\n",index,next_start);
        printf("range of t %d: %d\n\n",index,range_data -> range);

        next_start += range_data -> range;
        rest--;
    }
    return;

}

}
// n anzahl sequenzen
// k anzahl von ergebnissen
// i 
// j 
//
