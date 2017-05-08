#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <immintrin.h>
#include <stdio.h>

// CITATION: help from https://github.com/andikleen/tsx-tools
// https://clang.llvm.org/doxygen/rtmintrin_8h.html

#define RETRY_CON (3)
#define RETRY_CAP (1)
#define RETRY_OTHER (3)
#define UNLOCKED (0)
#define LOCKED (1)

void __attribute__((noinline, weak)) trace_abort(unsigned status) {}

int mutex_create(mutex_t *m)
{
  m->lock = UNLOCKED;
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

  for (i = 0; i < retry; i++) {
    printf("abotu to xbegin\n");
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
        return;
      }
      
      // otherwise, if someone is holding the lock, then we want 
      // to abort since it doesnt make sense to use transactions if the lock
      // thing is being used presently
      _xabort(0xff);
    }
    printf("OOPS didnt work out!! status = %d %u\n", status, status);
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
        //pause();
      /* Could do various kinds of backoff here. */
    } else if (status & _XABORT_CAPACITY) {
      retry = RETRY_CAP;
    } else {
      retry = RETRY_OTHER;
    }
  }
  /* Could do adaptation here */

  while (!__sync_bool_compare_and_swap(&(m->lock), UNLOCKED, LOCKED)) {
    //do
    //  pause();
    while (!lock_is_free(m));
    /* Could do respeculation here */
  }
}

void mutex_unlock(mutex_t *m)
{
  if (lock_is_free(m))
    _xend();
  else
    m->lock = UNLOCKED;
}
