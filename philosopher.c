#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "errors.h"
#include "log.h"
#include "random.h"

#include "dining_table.h"
#include "philosopher.h"

static void sleep_random_range_ms(int min, int max)
{
  int sleeptime_ms = random_from_range(min, max);
  usleep(1000 * sleeptime_ms);
}

#define SLEEP_RANDOM_RANGE(range_name) \
  sleep_random_range_ms(range_name ## _MIN_MS, range_name ## _MAX_MS)

static void philosopher_dine(philosopher_t * philosopher)
{
  log_dinner(philosopher->id);

  SLEEP_RANDOM_RANGE(PHILOSOPHER_DINNER_TIME_RANGE);
}

static void philosopher_think(philosopher_t * philosopher)
{
  log_think(philosopher->id);

  SLEEP_RANDOM_RANGE(PHILOSOPHER_THINKING_TIME_RANGE);
}

static void get_both_forks(philosopher_t * philosopher,
                           fork_t ** p_left_fork,
                           fork_t ** p_right_fork)
{
  dining_table_t * table = philosopher->dining_table;

  *p_left_fork  = dining_table_left_fork_get(table, philosopher);
  *p_right_fork = dining_table_right_fork_get(table, philosopher);
}

static void determine_forks_order(fork_t * last_busy_fork,
                                  fork_t ** p_first_fork,
                                  fork_t ** p_second_fork)
{
  if (last_busy_fork == *p_first_fork)
  {
    *p_first_fork  = *p_second_fork;
    *p_second_fork = last_busy_fork;
  }
}

static bool philosopher_try_dine(philosopher_t * philosopher, fork_t ** p_busy_fork)
{
  assert(philosopher->dining_table != NULL);

  dining_table_t * table = philosopher->dining_table;

  fork_t * first_fork, * second_fork;

  get_both_forks(philosopher, &first_fork, &second_fork);
  determine_forks_order(*p_busy_fork, &first_fork, &second_fork);

  fork_t * busy_fork = second_fork; /* Only second_fork can be returned as busy */

  fork_wait_take(first_fork);

  if (fork_try_take(second_fork))
  {
    philosopher_dine(philosopher);

    busy_fork = NULL;

    fork_release(second_fork);
  }

  fork_release(first_fork);

  *p_busy_fork = busy_fork;

  return busy_fork == NULL;
}

static void philosopher_dining_behavior_loop(philosopher_t * philosopher)
{
  fork_t * busy_fork = NULL;

  while (true)
  {
    philosopher_think(philosopher);

    while (!philosopher_try_dine(philosopher, &busy_fork))
    {
      log_wait_forks(philosopher->id);
    }
  }
}

static void * philosopher_thread_routine(void * context)
{
  philosopher_t * philosopher = context;

  philosopher_dining_behavior_loop(philosopher);

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
