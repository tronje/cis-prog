/*
 * Oliver Heidmann,
 * Tronje Krabbe,
 * Jorim Kornblueh
 */

#define dollyA  false
#define dollyB  true
#define randomNumber(x)  rand() % x

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void delete_population(bool* pop)
{
    if (pop == NULL)
        exit(EXIT_FAILURE);

    free(pop);
}

bool* create_new_population(unsigned int num_of_dollyA,
                            unsigned int num_of_dollyB)
{
    unsigned int index = 0;
    bool* new_bacteriaPool =  malloc(sizeof(bool) *
                            (num_of_dollyA + num_of_dollyB));
    if(new_bacteriaPool == NULL)
    {
        fprintf(stderr, "Error while allocating memory block"
                "bacteriaPool: file: simu_evolution");
        exit(EXIT_FAILURE);
    }

    for(;index < num_of_dollyA;index++)
    {
        new_bacteriaPool[index] = false;
    }
    for(;index < num_of_dollyB + num_of_dollyA; index++)
    {
        new_bacteriaPool[index] = true;  
    }
    return new_bacteriaPool;
}

void simulate_growth(unsigned int num_of_dollyA,
                     float pA,
                     unsigned int num_of_dollyB,
                     float pB,
                     unsigned int max_generations,
                     char* filePath)
{
    bool *bacteriaPool = create_new_population(num_of_dollyA,num_of_dollyB);
    unsigned int num_of_bacteria = num_of_dollyA + num_of_dollyB;
    unsigned int current_generation = 0;
    unsigned int bacteria_index = 0;
    unsigned int current_num_of_[2];
    float split_chance_of_[2];
    unsigned int random_Number;
    current_num_of_[dollyA] = num_of_dollyA;
    current_num_of_[dollyB] = num_of_dollyB;
    split_chance_of_[dollyA] = pA;
    split_chance_of_[dollyB] = pB;

    bool current_type;
    bool current_delete;

    FILE* fp;
    if(filePath != NULL)
    {
        fp = fopen(filePath,"a");
    }
    srand(time(NULL)); 
    for(;current_generation < max_generations; current_generation++)
    {
        if(filePath != NULL)
        {
            fprintf(fp,"%u %u %u\n",
                    current_generation,
                    current_num_of_[dollyA],
                    current_num_of_[dollyB]);
        }
        for(bacteria_index = 0; bacteria_index < num_of_bacteria; bacteria_index++)
        {   
            random_Number = randomNumber(num_of_bacteria);
            current_type = bacteriaPool[bacteria_index];
            current_delete = bacteriaPool[random_Number];
            if(100.0 * split_chance_of_[current_type]
                        > (float)(randomNumber(100))) 
            { 
                current_num_of_[current_type] += 1;
                current_num_of_[current_delete] -= 1;
                bacteriaPool[random_Number] = current_type;
            }

            if(current_num_of_[dollyA] == 0)
            {
                if(filePath != NULL)
                {
                    fclose(fp);
                }
                printf("fixed:B  steps:%u\n",current_generation);
                free(bacteriaPool);
                return;
            }
            if(current_num_of_[dollyB] == 0)
            {
                if(filePath != NULL)
                {
                    fclose(fp);
                }
                printf("fixed:A  steps:%u\n",current_generation);
                free(bacteriaPool);
                return;
            }
        }
    }
    printf("simulation stopped after %u steps (A: %u B:%u)\n",
            current_generation,
            current_num_of_[dollyA],
            current_num_of_[dollyB]);
    fclose(fp);
    free(bacteriaPool);
}

int main(int argc, char** argv)
{
    char* filePath = NULL;
    if(argc > 7 || argc < 6)
    {
        fprintf(stderr, "Error: too many or too few arguments");
        return EXIT_FAILURE;
    }
    if(argc == 7)
    {
        filePath = argv[6];
    }
    simulate_growth(
            strtol(argv[1],NULL,10),
            atof(argv[2]),
            strtol(argv[3],NULL,10),
            atof(argv[4]),
            strtol(argv[5],NULL,10),
            filePath       
            );
    return EXIT_SUCCESS;
}
