/*
Heidmann
Kornblueh
Krabbe
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

FILE *fileread;
FILE *fileout;
off_t size;
char *out;

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

  fprintf(stderr, "%s\n", filename);

  /*
   * file meta data access only: never ever initiate file transfer
   * from parallel file system to a local node by an open call!   
   */

  status = stat(filename, &filestat);
  if (status == -1)
    {
      perror("filesize");
      exit(EXIT_FAILURE);
    }

  return (filestat.st_size);
}

void revers()
{
    int i = 0, j = size;
    char a , b;
    while(i < j)
    {
	a = out[i];
	b = out[j];
	if(a != 'A' && a != 'G' && a != 'C' && a != 'T')
	{
	    i++;
	    continue;
	}
	else if(b != 'A' && b != 'G' && b != 'C' && b != 'T')
	{
	    j--;
	    continue;
	}
	out[i] = b;
	out[j] = a;
	i++, j--;
    }
}

int main(int argc, char *argv)
{
    int currentChar;
    int i;
    fileread = fopen("ecoli.seq", "rb");
    fileout = fopen("ecoli.seq.rc", "wb");
    size = filesize("ecoli.seq");
    out = malloc(sizeof(out) * size);

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
    revers();
    for(i = 0;i < size ; i++)
    {
	fputc(out[i], fileout);
    }
    
    free(out);

    fclose(fileread);
    fclose(fileout);

    return EXIT_SUCCESS;
}
