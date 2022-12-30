#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "dining_table.h"

typedef struct philosopher_s
{
  size_t           id;
  pthread_t        thread;
  dining_table_t * dining_table;
} philosopher_t;

void philosopher_assign_id(philosopher_t * philosopher, size_t id);

void philosopher_dining_begin(philosopher_t * philosopher,
                               dining_table_t * dining_table);

#endif
