#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(DEBUG)

#define CHECK_STATUS(status, action_text)            \
  do {                                               \
    if (status != 0)                                 \
    {                                                \
      fprintf(stderr, "[ERROR] %s\n", action_text);  \
      fprintf(stderr, "        at \"%s\":%d: %s\n",  \
              __FILE__, __LINE__, strerror(status)); \
      abort();                                       \
    }                                                \
  } while (0)

#else

#define CHECK_STATUS(status, action_text)           \
  do {                                              \
    if (status != 0)                                \
    {                                               \
      fprintf(stderr, "[ERROR] %s\n", action_text); \
      abort();                                      \
    }                                               \
  } while (0)


#endif

#endif
