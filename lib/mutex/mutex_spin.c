#include <mutex_type.h>

#define UNLOCKED (0)
#define LOCKED (1)


void mutex_create(mutex_t *m)  {
  m->lock = UNLOCKED;
}

void mutex_lock(mutex_t *m) {
  // spin until it's true
  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED));
}

void mutex_unlock(mutex_t *m) {
  m->lock = UNLOCKED;
}