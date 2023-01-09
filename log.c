#include <pthread.h>
#include <stdio.h>

#include "log.h"

#define DINING_ASCII_SEQ        "\x1b[42m"
#define THINKING_ASCII_SEQ      "\x1b[47m"
#define WAITING_FORKS_ASCII_SEQ "\x1b[41m"

#define COMMON_ASCII_RESET      "\x1b[0m"

static pthread_mutex_t printf_mutex = PTHREAD_MUTEX_INITIALIZER;

#define LOG(format, ...)               \
do {                                   \
  pthread_mutex_lock(&printf_mutex);   \
  printf(format, __VA_ARGS__);         \
  fflush(stdout);                      \
  pthread_mutex_unlock(&printf_mutex); \
} while(0)

static void log_char_with_ascii_seq(const char * seq, char ch)
{
  LOG("%s%c%s", seq, ch, COMMON_ASCII_RESET);
}

void log_dinner(size_t philosopher_id)
{
  log_char_with_ascii_seq(DINING_ASCII_SEQ, (int) philosopher_id + '1');
}

void log_think(size_t philosopher_id)
{
log_char_with_ascii_seq(THINKING_ASCII_SEQ, (int) philosopher_id + '1');
}

void log_wait_forks(size_t philosopher_id)
{
  log_char_with_ascii_seq(WAITING_FORKS_ASCII_SEQ, (int) philosopher_id + '1');
}
