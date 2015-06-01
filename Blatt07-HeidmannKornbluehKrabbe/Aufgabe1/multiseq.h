#include <stdio.h>
#include <stdlib.h>

typedef struct Multiseq Multiseq;

struct Multiseq
{
	unsigned char** sequence_infos;
	unsigned char** sequences;
	unsigned long* sizes_of_sequence;
	unsigned int size;
	unsigned int next_free_space;
	unsigned int current_entrys;

};

Multiseq* gen_new_multiseq(unsigned int size);

void resize_multiseq(Multiseq* seq);

void multiseq_add_sequence(Multiseq* seq,unsigned char* sequence,unsigned char* sequence_info,unsigned long size);
