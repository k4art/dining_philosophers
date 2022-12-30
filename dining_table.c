#include <pthread.h>

#include "dining_table.h"

static void dining_table_forks_init(dining_table_t * table)
{
  for (size_t i = 0; i < DINING_TABLE_FORKS_NUMBER; i++)
  {
    fork_init(&table->forks[i]);
  }
}

static void dining_table_philosophers_assign_ids(dining_table_t * table)
{
  for (size_t i = 0; i < DINING_TABLE_PHILOSOPHERS_NUMBER; i++)
  {
    philosopher_assign_id(&table->philosophers[i], i);
  }
}

static void dining_table_forks_destory(dining_table_t * table)
{
  for (size_t i = 0; i < DINING_TABLE_FORKS_NUMBER; i++)
  {
    fork_destroy(&table->forks[i]);
  }
}

void dining_table_init(dining_table_t * table)
{
  dining_table_forks_init(table);
  dining_table_philosophers_assign_ids(table);
}

void dining_table_destory(dining_table_t * table)
{
  dining_table_forks_destory(table);
}

fork_t * dining_table_left_fork_get(dining_table_t * table, const philosopher_t * philosopher)
{
  size_t guest_idx = philosopher - table->philosophers;
  size_t fork_idx = (guest_idx + 1) % DINING_TABLE_FORKS_NUMBER;

  return &table->forks[fork_idx];
}

fork_t * dining_table_right_fork_get(dining_table_t * table, const philosopher_t * philosopher)
{
  size_t guest_idx = philosopher - table->philosophers;

  return &table->forks[guest_idx];
}

void dining_table_dinner_begin(dining_table_t * table)
{
  for (size_t i = 0; i < DINING_TABLE_PHILOSOPHERS_NUMBER; i++)
  {
    philosopher_dining_begin(&table->philosophers[i], table);
  }
}

void dining_table_dinner_wait_end(dining_table_t * table)
{
  for (size_t i = 0; i < DINING_TABLE_PHILOSOPHERS_NUMBER; i++)
  {
    pthread_join(table->philosophers[i].thread, NULL);
  }
}
