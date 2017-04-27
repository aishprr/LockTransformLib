#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <stdio.h>
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
  int tid = omp_get_thread_num();

  printf("waiting with number %d, tid = %d!!!\n", q_num, tid);
  
  /** Continuously wait until it's me chance, but only reads,
      no invalidations */
  while(m->lock_count != q_num) {
    #pragma omp flush
  }
  // {
  //   for (count = q_num; count < turn; count++);
  // }
  printf("got the lock %d!!\n", q_num);
}

void mutex_unlock(mutex_t *m)
{
  
  int tid = omp_get_thread_num();
  printf("here to unlock the lock -- my tid = %d!!!\n", tid);
  /* We should also check that the caller's TID matches mp->lock_tid. However,
      that entails a syscall, so it is left out for efficiency. */

  /** Pass on the lock to the next thread in line if any or to the
       next thread that asks for the lock. */
  
  //__sync_synchronize();
  m->lock_count++;
  #pragma omp flush 
  
  printf("Unlocked!!! and now lock_count %d!!!\n", m->lock_count);
}
