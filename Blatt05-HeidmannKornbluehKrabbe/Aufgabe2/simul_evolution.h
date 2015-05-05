#ifndef SIMUL_EVOLUTION_H
#define SIMUL_EVOLUTION_H

#include <stdbool.h>
void create_new_population(unsigned int num_of_dollyA, unsigned int num_of_dollyB;

void simulate_growth(bool* bacteriaPool,float pA, float pB, unsigned int max_generations, char* write_to_file);

void destroy_population(bool* bacteriaPool);

#endif
