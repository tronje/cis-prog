//#include "intset.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>  

#define BITS_FOR_SIZE(SIZE)     ((SIZE) * CHAR_BIT)
#define ELEM2SECTION(LOGVAL,X)  ((X) >> (LOGVAL))
#define SECTIONMINELEM(S)       ((S) << logsectionsize)

template<typename Basetype>
static bool binarysearch_is_member(const Basetype *leftptr,
                                   const Basetype *rightptr,
                                   Basetype elem)
{
  const Basetype *midptr;

  while (leftptr <= rightptr)
  {
    midptr = leftptr + (((unsigned long) (rightptr-leftptr)) >> 1);
    if (elem < *midptr)
    {
      rightptr = midptr-1;
    } else
    {
      if (elem > *midptr)
      {
        leftptr = midptr + 1;
      } else
      {
        return true;
      }
    }
  }
  return false;
}

template<typename Basetype>
IntSet<Basetype>::~IntSet()
{
  free(elements);
  free(sectionstart);
}
template<typename Basetype>
IntSet<Basetype>::IntSet(unsigned long new_maxelement,unsigned long new_nofelements)
{
 // IntSet *intset = malloc(sizeof *intset);
  unsigned long idx;

  elements = (Basetype*)malloc(sizeof(Basetype) * new_nofelements);
  assert(elements != NULL);
  nextfree = 0;
  logsectionsize = BITS_FOR_SIZE(sizeof(Basetype));
  numofsections = ELEM2SECTION(logsectionsize,new_maxelement) + 1;
  std::cout << "ELEM2SECTION:" << ELEM2SECTION(logsectionsize,new_maxelement) + 1 << std::endl;
  sectionstart = (unsigned long*)malloc((sizeof (sectionstart) * (new_nofelements + 1)));
  assert(sectionstart != NULL);
  sectionstart[0] = 0;
  for (idx = 1; idx <= numofsections; idx++)
  {
    sectionstart[idx] = new_nofelements;
  }
  maxelement = new_maxelement;
  currentsectionnum = 0;
  nofelements = new_nofelements;
  previouselem = ULONG_MAX;
}

template<typename Basetype>
size_t IntSet<Basetype>::size(unsigned long maxelement,unsigned long nofelements)
{
  int logsectionsize = BITS_FOR_SIZE(sizeof (unsigned long));
  return sizeof (Basetype) * nofelements +
         sizeof (unsigned long) * (ELEM2SECTION(logsectionsize,maxelement) + 1);
};

template<typename Basetype>
void IntSet<Basetype>::add(unsigned long elem)
{
  // printf("===========>%lu\n",elem );
  // printf("===========>%lu\n",previouselem );
  // printf("===========>%lu\n\n",maxelement );
  assert(nextfree < nofelements &&
         elem <= maxelement &&
         (previouselem == ULONG_MAX || previouselem < elem));
  while (elem >= SECTIONMINELEM(currentsectionnum+1))
  {
    printf("===========>%lu\n",currentsectionnum );
    printf("===========>%lu\n\n",numofsections );
    assert(currentsectionnum < numofsections);
    sectionstart[currentsectionnum+1] = nextfree;
    currentsectionnum++;
  }
  assert(SECTIONMINELEM(currentsectionnum) <= elem &&
         elem < SECTIONMINELEM(currentsectionnum+1) &&
         ELEM2SECTION(logsectionsize,elem) ==
           currentsectionnum);
  elements[nextfree] = (Basetype) elem;
  nextfree++;
  previouselem = elem;
}

template<typename Basetype>
bool IntSet<Basetype>::is_member(unsigned long elem) const
{
  if (elem <= maxelement)
  {
    const unsigned long sectionnum = ELEM2SECTION(logsectionsize,elem);

    if (sectionstart[sectionnum] < sectionstart[sectionnum+1])
    {
      return binarysearch_is_member(
        elements + sectionstart[sectionnum],
        elements + sectionstart[sectionnum+1] - 1,
        (Basetype) elem);
    }
  }
  return false;
}

template<typename Basetype>
void IntSet<Basetype>::pretty_print() const
{
  unsigned long idx, sectionnum = 0;

  assert(nextfree > 0);
  for (idx = 0; idx < nextfree; idx++)
  {
    while (idx >= sectionstart[sectionnum+1])
    {
      sectionnum++;
    }
    printf("%lu%s",SECTIONMINELEM(sectionnum) + elements[idx],
                   idx < nextfree - 1 ? "&" : "\\\\\n");
  }
  for (idx = 0; idx < nextfree; idx++)
  {
    printf("%hu%s",elements[idx],
                   idx < nextfree - 1 ? "&" : "\\\\\n");
  }
  sectionnum = 0;
  for (idx = 0; idx < nextfree; idx++)
  {
    while (idx >= sectionstart[sectionnum+1])
    {
      sectionnum++;
    }
    printf("%lu%s",sectionnum,
                   idx < nextfree - 1 ? "&" : "\\\\\n");
  }
  for (idx = 0; idx <= numofsections; idx++)
  {
    printf("%lu%s",sectionstart[idx],
                   idx < numofsections ? "&" : "\\\\\n");
  }
}

template<typename Basetype>
static unsigned long binarysearch_smallest_g(const Basetype *leftptr,
                                             const Basetype *rightptr,
                                             Basetype pos)
{
  const Basetype *midptr, *found = NULL, *leftorig = leftptr;

  assert(leftptr <= rightptr);
  if (pos < *leftptr)
  {
    return 0;
  }
  if (pos > *rightptr)
  {
    return 1UL + (unsigned long) (rightptr - leftptr);
  }
  assert(pos > *leftptr && pos < *rightptr);
  while (leftptr <= rightptr)
  {
    midptr = leftptr + ((unsigned long) (rightptr - leftptr) >> 1);
    if (pos < *midptr)
    {
      rightptr = midptr - 1;
    } else
    {
      found = midptr;
      if (pos > *midptr)
      {
        leftptr = midptr + 1;
      }
      else
        break;
    }
  }
  /* not allowed by exercise! */
  assert(*found != pos);
  assert(found != NULL && found >= leftorig);
  return 1UL + (unsigned long) (found - leftorig);
}

template<typename Basetype>
unsigned long IntSet<Basetype>::number_next_larger(unsigned long pos) const
{
  unsigned long sectionnum = ELEM2SECTION(logsectionsize,pos),
                result = sectionstart[sectionnum];

  assert(pos <= maxelement);

  if (pos > previouselem)
    return nofelements;

  if (sectionstart[sectionnum] < sectionstart[sectionnum+1])
  {
    result += binarysearch_smallest_g(
                     elements + sectionstart[sectionnum],
                     elements + sectionstart[sectionnum+1] - 1,
                     (Basetype) pos);
  }
  return result;
}

