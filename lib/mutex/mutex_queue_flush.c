#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <omp.h>

#define LOCK_WAIT ((char *)"Qflush lock wait time")

int mutex_create(mutex_t *m)
{
  m->lock_count = 0;
  m->queue_count = 0;
   
  return SUCCESS_RETVAL;
}

void mutex_lock(mutex_t *m)
{

  double tim = TIME_IN;

  int q_num = __sync_fetch_and_add(&(m->queue_count), 1);

#if defined(PROP_BACKOFF_LOOP) || defined(EXP_BACKOFF_LOOP)
  int wait = 1;
#endif
  
  /** Continuously wait until it's me chance, but only reads,
      no invalidations */
  while(m->lock_count != q_num)
  {
#ifdef PROP_BACKOFF_LOOP
    // back off for time proportional to your position in queue
    // just to be safe although this should never happen ever
    wait = MAX(0, q_num - m->lock_count);
    for(int i = 0; i < wait; i++);
#endif
#ifdef EXP_BACKOFF_LOOP
    for(int i = 0; i < wait; i++);
    wait = wait * EXP_FACTOR;
#endif
#ifdef YIELD_LOOP
    sched_yield();
#endif
    #pragma omp flush
  }
  
  TIME_OUT(tim, LOCK_WAIT);
}

void mutex_unlock(mutex_t *m)
{
  /** Pass on the lock to the next thread in line if any or to the
       next thread that asks for the lock. */
  
  m->lock_count++;
  #pragma omp flush 
}
