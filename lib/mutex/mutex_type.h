#ifndef _MUTEX_TYPE_H
#define _MUTEX_TYPE_H

typedef struct mutex {

  int lock;

} mutex_t;

void mutex_create(mutex_t *);
void mutex_destroy(mutex_t *);
void mutex_lock(mutex_t *);
void mutex_unlock(mutex_t *);


#endif /* _MUTEX_TYPE_H */