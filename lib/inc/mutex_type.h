#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H


// #ifdef __cplusplus
// extern "C" {
// #endif

//#define MUTEX_TRANSACTION_RTM (1)

typedef struct mutex {

// TODO: to add to CFLAGS -D in Makefile
#ifdef MUTEX_SPIN
  int lock;
#endif
#ifdef MUTEX_QUEUE_VOL
  volatile int lock_count;
  int queue_count;
#endif
#ifdef MUTEX_QUEUE_FLUSH
  int lock_count;
  int queue_count;
#endif
#ifdef MUTEX_MCS_TICKET
#endif
#ifdef MUTEX_TRANSACTION_RTM
  volatile int lock;
#endif
#ifdef MUTEX_TRANSACTION_HLE
  unsigned int lock;
#endif

} mutex_t;

int mutex_create(mutex_t *);
void mutex_lock(mutex_t *);
void mutex_unlock(mutex_t *);


// #ifdef __cplusplus
// }
// #endif

#endif /* _MUTEX_TYPE_H */