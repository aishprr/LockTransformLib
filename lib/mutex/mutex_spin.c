#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <stdio.h>
#include <sched.h>

#define UNLOCKED (0)
#define LOCKED (1)
#define LOCK_WAIT ((char *)"Spin lock wait time")

int mutex_create(mutex_t *m) {
  m->lock = UNLOCKED;
  return SUCCESS_RETVAL;
  
}

void mutex_lock(mutex_t *m) {
  // spin until it's true
  double tim = TIME_IN;
  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED)) {
#ifdef YIELD_LOOP
    sched_yield();
#endif
  }
  TIME_OUT(tim, LOCK_WAIT);
}

void mutex_unlock(mutex_t *m) {
  m->lock = UNLOCKED;
}
