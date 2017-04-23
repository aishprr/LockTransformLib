#include "mutex_type.h"
#include "../inc/common.h"


#define UNLOCKED (0)
#define LOCKED (1)


int mutex_create(mutex_t *m) {
  m->lock = UNLOCKED;
  return SUCCESS_RETVAL;
}

int mutex_lock(mutex_t *m) {
  // spin until it's true
  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED));
  return SUCCESS_RETVAL;
}

int mutex_unlock(mutex_t *m) {
  m->lock = UNLOCKED;
  return SUCCESS_RETVAL;
}