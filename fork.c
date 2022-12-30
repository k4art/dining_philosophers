#include <pthread.h>
#include <assert.h>
#include <errno.h>

#include "errors.h"
#include "fork.h"

// typedef struct fork_s
// {
//   pthread_mutex_t mutex;
// } fork_t;

void fork_init(fork_t * fork)
{
  assert(fork != NULL);

  pthread_mutex_init(&fork->mutex, NULL);
}

void fork_destroy(fork_t * fork)
{
  assert(fork != NULL);

  pthread_mutex_destroy(&fork->mutex);
}

bool fork_try_take(fork_t * fork)
{
  assert(fork != NULL);

  int status = pthread_mutex_trylock(&fork->mutex);

  if (status == EBUSY)
  {
    return false;
  }

  CHECK_STATUS(status, "Try to lock fork's mutex");
  return true;
}

void fork_wait_take(fork_t * fork)
{
  assert(fork != NULL);

  int status = pthread_mutex_lock(&fork->mutex);

  CHECK_STATUS(status, "Lock fork's mutex");
}

void fork_lock(fork_t * fork)
{
  assert(fork != NULL);

  pthread_mutex_lock(&fork->mutex);
}

void fork_release(fork_t * fork)
{
  assert(fork != NULL);

  int status = pthread_mutex_unlock(&fork->mutex);

  CHECK_STATUS(status, "Unlock fork's mutex");
}
