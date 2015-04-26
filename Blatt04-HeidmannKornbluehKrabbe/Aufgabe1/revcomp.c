/*
Heidmann
Kornblueh
Krabbe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

/*
 * The Open Group Base Specifications Issue 7
 * IEEE Std 1003.1, 2013 Edition
 * Copyright © 2001-2013 The IEEE and The Open Group
 */

// file size cannot be long as it is not assured that it can be stored in long (eg. ZFS) 
off_t filesize(char *filename)
{
  struct stat filestat;
  int         status;

  status = stat(filename, &filestat);
  if (status == -1)
    {
      perror("filesize");
      exit(EXIT_FAILURE);
    }

  return (filestat.st_size);
}

void revers(const int size, char *out)
{
    int i = 0, j = size-1;
    char a , b;
    
    while(i < j)
    {
	a = out[i];
	b = out[j];
	
	if(a != 'A' && a != 'G' && a != 'C' && a != 'T')
	{
	    i++;
	}
	else if(b != 'A' && b != 'G' && b != 'C' && b != 'T')
	{
	    j--;
	}
	else
	{
	    out[i] = b;
	    out[j] = a;
	    i++, j--;
	}
    }
}

int main(int argc, char *argv[])
{
    FILE *fileread = NULL;
    FILE *fileout = NULL;

    off_t size = 0;
    
    char *out = NULL;
    
    int currentChar;
    int i;
    char fileoutname[FILENAME_MAX];
    
    if(argc != 2)
    {
	fprintf(stderr, "invalide input!\nUsage: ./revcomp.x filename");
	exit(EXIT_FAILURE);
    }

    /*
      why does strncpy(fileoutname, argv[1], strlen(argv[1])) produce 
      Conditional jump or move depends on uninitialised value(s)
      at 0x7E8A: strlen (vg_replace_strmem.c:427)
     */

    strcpy(fileoutname, argv[1]);
    strncat(fileoutname, ".rc", 3);
    
    fileread = fopen(argv[1], "r");
    if(fileread == NULL)
	exit(EXIT_FAILURE);
    
    fileout = fopen(fileoutname , "w");
    if(fileout == NULL)
	exit(EXIT_FAILURE);
    
    size = filesize(argv[1]);
    if((out = malloc(sizeof(char) * size)) == NULL)
	exit(EXIT_FAILURE);

    for(i = 0;(currentChar = fgetc(fileread)) != EOF ; i++)
    {
	switch((char)currentChar)
	{
	case 'A':
	    *(out + i) = 'T'; break;
	case 'C':
	    *(out + i) = 'G'; break;
	case 'G':
	    *(out + i) = 'C'; break;
	case 'T':
	    *(out + i) = 'A'; break;
	default:
	    *(out + i) = (char)currentChar;
        }
    }
    
    revers(size, out);

    for(i = 0;i < size ; i++)
    {
	fputc(out[i], fileout);
    }
    
    free(out);

    fclose(fileread);
    fclose(fileout);

    return EXIT_SUCCESS;
}
