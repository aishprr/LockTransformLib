#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <immintrin.h>
#include <stdio.h>
#include <omp.h>
#include <sched.h>

// CITATION: guidance from https://github.com/andikleen/tsx-tools
// https://clang.llvm.org/doxygen/rtmintrin_8h.html

#define RETRY_CON (3)
#define RETRY_CAP (1)
#define RETRY_OTHER (3)
#define UNLOCKED (0)
#define LOCKED (1)
#define HYPERTHREADS (16)
#define THRESHOLD (5)

void __attribute__((noinline, weak)) trace_abort(unsigned status) {}

int mutex_create(mutex_t *m)
{
  m->lock = UNLOCKED;
  m->trans_wait = 0;
  return SUCCESS_RETVAL; 
}

static inline int lock_is_free(mutex_t *m)
{
  return (m->lock == UNLOCKED);
}

void mutex_lock(mutex_t *m)
{
  unsigned i;
  unsigned status = 0;
  unsigned retry = RETRY_OTHER;
  int tid = omp_get_thread_num();
  int tried = 0;

  for (i = 0; i < retry; i++) {
    dbg_printf("abotu to xbegin\n");
    if (m->trans_wait > THRESHOLD) {
      dbg_printf("didnt try\n");
      break;
      // dont even try for transactions
    } else {
      tried = 1;
      __sync_fetch_and_add(&m->trans_wait, 1);
    }
    if ((status = _xbegin()) == _XBEGIN_STARTED) {
      // now if the lock is free, that means that 
      // no one is holding a lock, so we're good to go 
      // on the transaction
      if (lock_is_free(m)) {
        // add the lock to the read set so that if someone aborts, 
        // then the person doing the transaction will also get
        // aborted
        // TDODO: Can also try to wait for all transactions to be over
        // and check that atomically somehow
        __sync_fetch_and_add(&m->trans_wait, -1);
        return;
      }
      
      // otherwise, if someone is holding the lock, then we want 
      // to abort since it doesnt make sense to use transactions if the lock
      // thing is being used presently
      _xabort(0xff);
    } else {
      // you tried, but didnt get the thing
      // you did not abort
      __sync_fetch_and_add(&m->trans_wait, -1);
    }
    dbg_printf("OOPS didnt work out!! status = %d %u\n", status, status);
    trace_abort(status);
    if ((status & _XABORT_EXPLICIT) && _XABORT_CODE(status) == 0xff) {
      while (!lock_is_free(m));
      // wait to hold the lock now since there was an explicit abort

    } else if (!(status & _XABORT_RETRY) && !(status & _XABORT_CAPACITY)) {
      // just try to get the lock since this is not going to work 
      // out with transactions
      break;
    }
      
    if (status & _XABORT_CONFLICT) {
      retry = RETRY_CON;
      while (!lock_is_free(m));
      // There was a conflict, so now try again with the transactions
      /* Could do various kinds of backoff here. */
    } else if (status & _XABORT_CAPACITY) {
      retry = RETRY_CAP;
    } else {
      retry = RETRY_OTHER;
    }
  }
  /* Could do adaptation here */
#ifdef DROPPED_COUNT
  if (!tried) {
      // want to count only those who actually dropped not those who
      // gave up
      dbg_printf("TID %d dropped in trial %d\n", tid, i);
  } else {
    // I tried but failed
    dbg_printf("%d\n", i);
  }
  // for average retrials 
  
#endif
  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED))
  {
    sched_yield();
  }
}

void mutex_unlock(mutex_t *m)
{
  if (lock_is_free(m)) {
    _xend();
  }
  else {
    m->lock = UNLOCKED;
  }
  dbg_printf("done unlocking!!\n");
}
