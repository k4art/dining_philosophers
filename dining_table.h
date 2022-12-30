#ifndef DINING_TABLE_H
#define DINING_TABLE_H

typedef struct dining_table_s dining_table_t;

#include "config.h"

#include "philosopher.h"
#include "fork.h"

#define DINING_TABLE_FORKS_NUMBER DINING_TABLE_PHILOSOPHERS_NUMBER

struct dining_table_s
{
  philosopher_t philosophers[DINING_TABLE_PHILOSOPHERS_NUMBER];
  fork_t        forks[DINING_TABLE_FORKS_NUMBER];
};

void dining_table_init(dining_table_t * table);
void dining_table_destory(dining_table_t * table);

void dining_table_dinner_begin(dining_table_t * table);
void dining_table_dinner_wait_end(dining_table_t * table);

fork_t * dining_table_left_fork_get(dining_table_t * table, const philosopher_t * philosopher);
fork_t * dining_table_right_fork_get(dining_table_t * table, const philosopher_t * philosopher);

#endif
