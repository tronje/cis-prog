#ifndef CHECKALLOC_H
#define CHECKALLOC_H

#define CHECK(p) \
    if((p) == NULL) \
{ \
      perror("The following error has occured"); \
      exit(EXIT_FAILURE); \
}

#endif
