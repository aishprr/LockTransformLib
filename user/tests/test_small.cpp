#include "../../lib/mutex/mutex_type.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>

#define PARALLEL_ADDS (100)

int matrix_multiply()
{
  return 1;
}

int main() {

  mutex_t mu;
  mutex_create(&mu);

  int i = 0;
  #pragma omp parallel for num_threads(PARALLEL_ADDS)
  for(int u = 0; u < PARALLEL_ADDS; u++)
  {
    int tid = omp_get_thread_num();
    int cpu_num = sched_getcpu();
    printf("thread %d on CPU %d\n", tid, cpu_num);
  
    printf("thread number inside %d\n", tid);
    mutex_lock(&mu);
    i = i + 1;
    mutex_unlock(&mu);
  }

  printf("i = %d\n", i);


  return 1;
}
