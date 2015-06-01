#include <stdio.h>
#include <stdlib.h>
#include "multiseq.h"


Multiseq* gen_new_multiseq(unsigned int size)
{
	Multiseq* new_multiseq = malloc(size * (sizeof(char**) + sizeof(char**) + sizeof(unsigned int*)));
	if(new_multiseq == NULL) exit( EXIT_FAILURE );
	new_multiseq -> sequences = malloc(sizeof(char*) * size);
	if(new_multiseq -> sequences == NULL) exit( EXIT_FAILURE );
	new_multiseq -> sequence_infos = malloc(sizeof(char*) * size);
	if(new_multiseq -> sequence_infos== NULL) exit( EXIT_FAILURE );
	new_multiseq -> sizes_of_sequence =  malloc(sizeof(unsigned int) * size);
		if(new_multiseq -> sizes_of_sequence == NULL) exit( EXIT_FAILURE );
	new_multiseq -> size = size;
	new_multiseq -> next_free_space = 0;
	new_multiseq -> current_entrys = 0;

	return new_multiseq;
}

void resize_multiseq(Multiseq* seq)
{
	seq -> sequences = realloc(seq -> sequences, seq -> size * 2 * sizeof(char**));
	seq -> sequence_infos = realloc(seq -> sequence_infos, seq -> size * 2 * sizeof(char**));
	seq -> sizes_of_sequence = realloc(seq -> sizes_of_sequence,seq -> size * 2 * sizeof(unsigned int));
}

void multiseq_add_sequence(Multiseq* seq,unsigned char* sequence,unsigned char* sequence_info,unsigned long size)
{
	seq -> sequences[seq -> next_free_space] = sequence;
	seq -> sequence_infos[seq -> next_free_space] = sequence_info;
	seq -> sizes_of_sequence[seq -> next_free_space] = size;
	seq -> next_free_space++;
	seq -> current_entrys++;
}