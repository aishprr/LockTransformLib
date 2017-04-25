#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H

typedef struct mutex {

// TODO: to add to CFLAGS -D in Makefile
//#ifdef MUTEX_SPIN
  int lock;
//#endif
//#ifdef MUTEX_QUEUE
  int lock_count;
  int queue_count;
//#endif
//#ifdef MUTEX_MCS_TICKET
//#endif

// #ifdef MUTEX_TRANSACTION_1

//#endif

} mutex_t;

int mutex_create(mutex_t *);
void mutex_lock(mutex_t *);
void mutex_unlock(mutex_t *);


#endif /* _MUTEX_TYPE_H */