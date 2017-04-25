#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <stdio.h>

int mutex_create(mutex_t *m)
{
  m->lock_count = 0;
  m->queue_count = 0;
   
  return SUCCESS_RETVAL;
}

void mutex_lock(mutex_t *m)
{

  int q_num = __sync_fetch_and_add(&m->queue_count, 1);

  printf("waiting with number %d!!!\n", q_num);
  
  /** Continuously wait until it's me chance, but only reads,
      no invalidations */
  while(m->lock_count != q_num) {
    printf("q_num = %d lock_count = %d", q_num, m->lock_count);
  }
  printf("got the lock %d!!\n", q_num);
}

void mutex_unlock(mutex_t *m)
{
  printf("here to unlock the lock!!!\n");
  /* We should also check that the caller's TID matches mp->lock_tid. However,
      that entails a syscall, so it is left out for efficiency. */

  /** Pass on the lock to the next thread in line if any or to the
       next thread that asks for the lock. */
  m->lock_count++;//__sync_fetch_and_add(&m->lock_count, 1);
  printf("Unlocked!!! and now lock_count %d!!!\n", m->lock_count);
}
