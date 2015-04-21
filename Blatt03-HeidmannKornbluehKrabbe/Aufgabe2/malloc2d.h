/*
Heidmann
Krabbe
Kornblueh
 */
#define malloc2d(ARR2D, ROWS, COLS)\
  {\
    unsigned long idx;\
    ARR2D = malloc(sizeof (*ARR2D) * (ROWS));\
    (ARR2D)[0] = malloc(sizeof (**ARR2D) * (COLS) * (ROWS));\
    for(idx = 1UL; idx < (ROWS); idx++)\
      (ARR2D)[idx] = (ARR2D)[idx-1] + (COLS);\
  }

#define free2d(ARR2D)\
  if((ARR2D) != NULL)\
  {\
    free((ARR2D)[0]);\
    free(ARR2D);\
  }
