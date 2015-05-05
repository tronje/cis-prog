#define dollyA  false
#define dollyB  true
#define randomNumber(x)  rand() % x + 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
void delete_population(bool* pop)
{
    free(pop);
}

bool* create_new_population
        (
        unsigned int num_of_dollyA,
        unsigned int num_of_dollyB
        )
{
    unsigned int index = 0;
    bool* new_bacteriaPool =  malloc(sizeof(bool) * (num_of_dollyA + num_of_dollyB));
    if(new_bacteriaPool == NULL)
    {
        puts("Error while allocating memory block bacteriaPool: file: simu_evolution");
        return 0;
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

void simulate_growth
        (
        unsigned int num_of_dollyA,
        float pA,
        unsigned int num_of_dollyB,
        float pB,
        unsigned int max_generations,
        char* filePath
        )
{
    bool *bacteriaPool = create_new_population(num_of_dollyA,num_of_dollyB);
    unsigned int num_of_bacteria = num_of_dollyA + num_of_dollyB;
    unsigned int current_generation = 0;
    unsigned int bacteria_index = 0;
    unsigned int current_num_of_[2];
    current_num_of_[dollyA] = num_of_dollyA;
    current_num_of_[dollyB] = num_of_dollyB;
    float split_chance_of_[2];
    split_chance_of_[dollyA] = pA;
    split_chance_of_[dollyB] = pB;
    unsigned int random_Number;

    bool current_type;
    bool current_delete;
    
    srand(time(NULL)); 
    for(;current_generation < max_generations; current_generation++)
    {
        for(bacteria_index = 0; bacteria_index < num_of_bacteria; bacteria_index++)
        {   
            random_Number = randomNumber(num_of_bacteria);
            current_type = bacteriaPool[bacteria_index];
            //printf("%f\n",split_chance_of_[current_type]);
            current_delete = bacteriaPool[random_Number];
            if(split_chance_of_[current_type] == 1.0
                    ||(100.0 * split_chance_of_[current_type] > (float)(randomNumber(100)) 
                    && split_chance_of_[current_type] != 0.0))
            {   
            //printf("%d\n",current_type);
                current_num_of_[current_type] += 1;
                current_num_of_[current_delete] -= 1;
                bacteriaPool[random_Number] = current_type;
            }
        
            if(current_num_of_[dollyA] == 0)
            {
                if(filePath != NULL)
                {
                    FILE* fp = fopen(filePath,"a");
                    fprintf(fp,"fixed:B  steps:%u\n",current_generation);
                    fclose(fp);
                }
                else
                {
                    printf("fixed:B  steps:%u\n",current_generation);
                }
                return;
            }
            if(current_num_of_[dollyB] == 0)
            {
                if(filePath != NULL)
                {
                    FILE* fp = fopen(filePath,"a");
                    fprintf(fp,"fixed:A  steps:%u\n",current_generation);
                    fclose(fp);
                }
                else
                {
                    printf("fixed:A  steps:%u\n",current_generation);
                }
                return;
            }
        }
    }
    printf("simulation stopped after %u steps (A: %u B:%u)\n",
            current_generation, current_num_of_[dollyA], current_num_of_[dollyB]);
            return;

}

int main(int argc, char** argv)
{
    char* filePath = NULL;
    if(argc > 7 || argc <= 1)
    {
        puts("Error to many or to few arguments");
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
    return 1;
}
