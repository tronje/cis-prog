#include <stdio.h>

void usage(void)
{
  fprintf(stderr, "Usage: leapyear.x yearToTest\n");
}

int main(int argc, char *argv[])
{
  int year;
  if (argc == 2)
    {
      if (sscanf(argv[1], "%d", &year))
	{
	  if(!(year % 4) && ((year % 100) || !(year % 400)))
	    printf("The year %d is an leapyear.\n", year);
	  else
	    printf("The year %d is no leapyear.\n", year);
	}      
      else
	{
	  fprintf(stderr, "invalid input\n");
	  usage();
	}    
    }
  else
    {
      fprintf(stderr, "wrong number of arguments\n");
      usage();
    }
  return 0;
}
