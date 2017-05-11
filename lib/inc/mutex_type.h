#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H

typedef struct mcs_queue_node mcs_qnode;

struct mcs_queue_node {
  volatile mcs_qnode *next;
  int wait;
};


typedef struct mutex {

#ifdef MUTEX_SPIN
  volatile int lock;
#endif
#ifdef MUTEX_QUEUE_VOL
  volatile int lock_count;
  int queue_count;
#endif
#ifdef MUTEX_QUEUE_FLUSH
  int lock_count;
  int queue_count;
#endif
#ifdef MUTEX_MCS_QUEUE
  volatile mcs_qnode *queue_end;
#endif
#ifdef MUTEX_TRANSACTION_RTM
  volatile int lock;
#endif
#ifdef MUTEX_TRANSACTION_HLE
  volatile unsigned int lock;
#endif

} mutex_t;

int mutex_create(mutex_t *);
void mutex_lock(mutex_t *);
void mutex_unlock(mutex_t *);


#endif /* _MUTEX_TYPE_H */