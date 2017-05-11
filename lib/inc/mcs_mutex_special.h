#ifndef _MCS_MUTEX_TYPE_H
#define _MCS_MUTEX_TYPE_H

typedef struct mcs_queue_node mcs_qnode;

struct mcs_queue_node {
  volatile mcs_qnode *next;
  int wait;
};


typedef struct mcs_mutex {
} mcs_mutex_t;

int mcs_mutex_create(mcs_mutex_t *);
void mcs_mutex_lock(mcs_mutex_t *);
void mcs_mutex_unlock(mcs_mutex_t *);

#endif /* _MCS_MUTEX_TYPE_H */