#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <immintrin.h>

int mutex_create(mutex_t *m)
{
  m->trans_status = _XABORT_EXPLICIT;
  return SUCCESS_RETVAL; 
}

void mutex_lock(mutex_t *m)
{
  int max_tries = 1;
  for (int n_tries = 0; n_tries < max_tries; n_tries++) {
    m->trans_status = _xbegin ();
    if (m->trans_status == _XBEGIN_STARTED || !(m->trans_status & _XABORT_RETRY))
      break;
  }
  if (m->trans_status != _XBEGIN_STARTED) {
    // lock the thing
  } 
  
}

void mutex_unlock(mutex_t *m)
{
  if (m->trans_status == _XBEGIN_STARTED) 
  {
    _xend ();
  } else {

  }
  
}
