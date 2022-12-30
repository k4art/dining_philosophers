#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "errors.h"

#include "dining_table.h"
#include "philosopher.h"

static void philosopher_dine(philosopher_t * philosopher)
{
  sleep(PHILOSOPHER_DINNER_TIME_SEC);
}

static void philosopher_think(philosopher_t * philosopher)
{
  printf("%zu thinking...\n", philosopher->id);
}

static bool philosopher_try_dine(philosopher_t * philosopher, fork_t ** p_busy_fork)
{
  assert(philosopher->dining_table != NULL);

  dining_table_t * table = philosopher->dining_table;

  fork_t * left_fork  = dining_table_left_fork_get(table, philosopher);
  fork_t * right_fork = dining_table_right_fork_get(table, philosopher);

  if (*p_busy_fork == right_fork)
  {
    fork_t * temp = left_fork;
    left_fork = right_fork;
    right_fork = temp;
  }

  fork_t * busy_fork;

  busy_fork = left_fork;

  fork_wait_take(left_fork);
  {
    busy_fork = right_fork;
    if (fork_try_take(right_fork))
    {
      printf("%zu DINNER TIME!\n", philosopher->id);
      philosopher_dine(philosopher);

      busy_fork = NULL;

      fork_release(right_fork);
    }

    fork_release(left_fork);
  }

  *p_busy_fork = busy_fork;

  return busy_fork == NULL;
}

static void philosopher_dining_behavior_start(philosopher_t * philosopher)
{
  fork_t * busy_fork = NULL;

  printf("%zu STARTED\n", philosopher->id);

  while (!philosopher_try_dine(philosopher, &busy_fork))
  {
    philosopher_think(philosopher);
  }

  printf("%zu DONE\n", philosopher->id);
}

static void * philosopher_thread_routine(void * context)
{
  philosopher_t * philosopher = context;

  philosopher_dining_behavior_start(philosopher);

  return NULL;
}

void philosopher_assign_id(philosopher_t * philosopher, size_t id)
{
  assert(philosopher != NULL);

  philosopher->id = id;
}

void philosopher_dining_begin(philosopher_t * philosopher, dining_table_t * dining_table)
{
  philosopher->dining_table = dining_table;

  int status = pthread_create(&philosopher->thread, NULL, philosopher_thread_routine, philosopher);

  CHECK_STATUS(status, "Creating thread for a philosopher");
}
