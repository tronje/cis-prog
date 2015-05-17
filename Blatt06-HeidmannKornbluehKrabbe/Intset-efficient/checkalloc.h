#ifndef CHECKALLOC_H
#define CHECKALLOC_H

#define CHECK(p) \
    if((p) == NULL) \
{ \
      perror("Error in %s, line %d)", \
                        __FILE__, __LINE__); \
      exit(EXIT_FAILURE); \
}

#endif
