#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "random.h"

typedef struct random_pool_s
{
  int values[RANDOM_POOL_SIZE];
  size_t next_idx;
  pthread_mutex_t mutex;
} random_pool_t;

static random_pool_t m_random_pool =
{
  .mutex = PTHREAD_MUTEX_INITIALIZER,
};

static int random_pool_next(void)
{
  pthread_mutex_lock(&m_random_pool.mutex);

  int next_value = m_random_pool.values[m_random_pool.next_idx];

  m_random_pool.next_idx = (m_random_pool.next_idx + 1) % RANDOM_POOL_SIZE;

  pthread_mutex_unlock(&m_random_pool.mutex);

  return next_value;
}

static void random_pool_init(void)
{
  srand(time(NULL));

  for (size_t i = 0; i < RANDOM_POOL_SIZE; i++)
  {
    m_random_pool.values[i] = rand();
  }
}

/* Not thread-safe. */
int random_init(void)
{
  random_pool_init();
}

int random_from_range(int min, int max)
{
  assert(max > min);
  assert(max > 0 && min >= 0);

  return random_pool_next() % (max - min + 1) + min;
}
