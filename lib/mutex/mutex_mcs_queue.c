#include "../inc/mutex_type.h"
#include "../inc/common.h"
#include <omp.h>
#include <stddef.h>
#include <stdio.h>

mcs_qnode *common_global_node_ptr;
#pragma omp threadprivate(common_global_node_ptr)

int mutex_create(mutex_t *m)
{
  m->queue_end = NULL;
  dbg_printf("queue end value %p\n", m->queue_end);
  dbg_printf("size = %d\n", sizeof(mutex_t));
  return SUCCESS_RETVAL;
}

void mutex_lock(mutex_t *m)
{

  dbg_printf("start of lock func queue end value %p\n", m->queue_end);

  common_global_node_ptr = (mcs_qnode *)malloc(sizeof(mcs_qnode));
  mcs_qnode *node= common_global_node_ptr;
  dbg_printf("common global ptr %p\n", (void *)(common_global_node_ptr));

  node->next = NULL;

  dbg_printf("end of lock func queue end value %p\n", m->queue_end);
  
  // I want to be the person everyone sees as the end of the queue
  volatile mcs_qnode *prev_end = __sync_lock_test_and_set(&m->queue_end, node);
  if (prev_end != NULL) {
    dbg_printf("prev_end not NULL %p\n", prev_end);
    // add myself to the queue and then just wait to be woken up kind of
    dbg_printf("node pointer is %p\n", node);
    node->wait = 1;
    dbg_printf("set to 1 wait %p\n", node);
    prev_end->next = node;

    dbg_printf("prev_end value got here\n");

    // wait until previous lock holder acknowledges this thread
    while (node->wait);
  }
}

void mutex_unlock(mutex_t *m)
{
  //is there someone after me right now?
  mcs_qnode *node = common_global_node_ptr;
  if (!node->next) {
    // check if I am the end still and if yes, then return
    // they will see the NULL and take the lock
    if (__sync_bool_compare_and_swap(&m->queue_end, node, NULL)) {
      return;
    }
    // if not, then they didnt set my next yet, but they have added themselves
    // to the queue and must be woken up by me otherwise it will deadlock
    
    // wait for them to set it
    while (!node->next);
  }
  
  // release the person now that we know who they are
  node->next->wait = 0;
}
