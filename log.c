#include <pthread.h>
#include <stdio.h>

#include "log.h"

#define LOG_CHARS_PER_LINE 30

#define DINING_ASCII_SEQ        "\x1b[42m"
#define THINKING_ASCII_SEQ      "\x1b[47m"
#define WAITING_FORKS_ASCII_SEQ "\x1b[41m"

#define COMMON_ASCII_RESET      "\x1b[0m"

static int m_current_line_chars_counter = 0;
static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

static void log_char_with_ascii_seq(const char * seq, char ch)
{
  pthread_mutex_lock(&m_mutex);
  printf("%s%c%s", seq, ch, COMMON_ASCII_RESET);

  m_current_line_chars_counter++;

  if (m_current_line_chars_counter == LOG_CHARS_PER_LINE)
  {
    printf("\n");
    m_current_line_chars_counter = 0;
  }
  else
  {
    fflush(stdout);
  }

  pthread_mutex_unlock(&m_mutex);
}

#if DINING_TABLE_PHILOSOPHERS_NUMBER > 27
#error log module cannot handle more than 27 philosophers
#endif

void log_dinner(size_t philosopher_id)
{
  log_char_with_ascii_seq(DINING_ASCII_SEQ, (int) philosopher_id + 'a');
}

void log_think(size_t philosopher_id)
{
#if !defined(LOG_ONLY_DINING)
  log_char_with_ascii_seq(THINKING_ASCII_SEQ, (int) philosopher_id + 'a');
#endif
}

void log_wait_forks(size_t philosopher_id)
{
#if !defined(LOG_ONLY_DINING)
  log_char_with_ascii_seq(WAITING_FORKS_ASCII_SEQ, (int) philosopher_id + 'a');
#endif
}
