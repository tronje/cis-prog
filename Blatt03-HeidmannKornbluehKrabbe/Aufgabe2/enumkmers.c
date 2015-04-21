/*
   Krabbe
   Kornblueh
   Heidmann
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "malloc2d.h"

void usage()
{
    printf("invalide usage\nenumkmers.x letters wordlength\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        usage();
    }
    char *s = argv[1];
    char *a = malloc(sizeof a * strlen(argv[2]));
    char **out; 
    int lenabc = strlen(s);
    int wordlen;

    if(sscanf(argv[2], "%d%s", &wordlen, a)!=1)
    {
        usage();
    }
    free(a);

    malloc2d(out, (int) pow(lenabc, wordlen), wordlen+1);

    for(int i = 1; i <= wordlen; i++)
    {
        int cycle = (int)pow(lenabc, i);
        int num = (int)pow(lenabc, (wordlen - (i-1))-1);

        for(int j = 0; j < cycle; j++)
        {
            for(int k = 0; k < num ; k++)
            {
                out[j*num + k][i-1] = s[j%lenabc];
            }
        }
    }
    for(int i = 0; i < (int) pow(lenabc, wordlen); i++)
    {
        printf("%s\n", out[i]);
    }
    free2d(out);
}
