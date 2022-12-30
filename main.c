#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "dining_table.h"

int main(void)
{
  dining_table_t table;

  dining_table_init(&table);

  dining_table_dinner_begin(&table);
  dining_table_dinner_wait_end(&table);

  return 0;
}
