#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H

typedef struct mutex {

#ifdef MUTEX_SPIN
  int lock;
#endif
#ifdef MUTEX_QUEUE
  int lock_count;
  int queue_count;
#endif

} mutex_t;

void mutex_create(mutex_t *);
void mutex_destroy(mutex_t *);
void mutex_lock(mutex_t *);
void mutex_unlock(mutex_t *);


#endif /* _MUTEX_TYPE_H */