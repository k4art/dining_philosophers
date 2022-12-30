#ifndef FORK_H
#define FORK_H

#include <pthread.h>
#include <stdbool.h>

typedef struct fork_s
{
  pthread_mutex_t mutex;
} fork_t;

void fork_init(fork_t * fork);
void fork_destroy(fork_t * fork);

bool fork_try_take(fork_t * fork);
void fork_wait_take(fork_t * fork);

void fork_wait_release(fork_t * fork);

void fork_release(fork_t * fork);

#endif
