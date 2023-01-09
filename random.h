#ifndef RANDOM_H
#define RANDOM_H

#include "config.h"

/* Not thread-safe. */
int random_init(void);
int random_from_range(int min, int max);

#endif
