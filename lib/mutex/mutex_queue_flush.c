#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <omp.h>

int mutex_create(mutex_t *m)
{
  m->lock_count = 0;
  m->queue_count = 0;
   
  return SUCCESS_RETVAL;
}

void mutex_lock(mutex_t *m)
{

  int q_num = __sync_fetch_and_add(&(m->queue_count), 1);
  
  /** Continuously wait until it's me chance, but only reads,
      no invalidations */
  while(m->lock_count != q_num)
  {
    #pragma omp flush
  }
  
}

void mutex_unlock(mutex_t *m)
{
  /** Pass on the lock to the next thread in line if any or to the
       next thread that asks for the lock. */
  
  m->lock_count++;
  #pragma omp flush 
}
