#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "random.h"
#include "dining_table.h"

static dining_table_t table;

static void initialize(void)
{
  random_init();
  dining_table_init(&table);
}

int main(void)
{
  initialize();

  dining_table_dinner_begin(&table);
  dining_table_dinner_wait_end(&table);

  return 0;
}
