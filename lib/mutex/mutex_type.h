#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H

#define MUTEX_SPIN 1
#define EXP_FACTOR (2)

typedef struct mutex {

#ifdef MUTEX_SPIN
  int lock;
#endif
#ifdef MUTEX_QUEUE
  int lock_count;
  int queue_count;
#endif
#ifdef MUTEX_MCS_TICKET
#endif

#ifdef MUTEX_TRANSACTION_1

#endif

} mutex_t;

int mutex_create(mutex_t *);
int mutex_lock(mutex_t *);
int mutex_unlock(mutex_t *);


#endif /* _MUTEX_TYPE_H */