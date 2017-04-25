#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <stdio.h>


#define UNLOCKED (0)
#define LOCKED (1)


int mutex_create(mutex_t *m) {
  m->lock = UNLOCKED;
  return SUCCESS_RETVAL;
}

void mutex_lock(mutex_t *m) {
  // spin until it's true
  printf("waiting!!!\n");
  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED));
  printf("got thelock!!");
}

void mutex_unlock(mutex_t *m) {
  printf("unlocked the lock!!");
  m->lock = UNLOCKED;
}