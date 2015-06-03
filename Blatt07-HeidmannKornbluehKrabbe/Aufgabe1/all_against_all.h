
typedef struct Thread_data Thread_data;

struct Thread_data
{
    Multiseq* seq;
    BestKVals* bestkvals;
    unsigned long start;
    unsigned long range;
};

int compare_dist(unsigned long a, unsigned long b);

void eval_seqrange(Multiseq* seq,
    unsigned long t,
    unsigned long k, 
    BestKVals* bestkvals);

void* insert_seqs_into_bestkval(void* thread_data);