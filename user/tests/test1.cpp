#include "../../lib/mutex/mutex_type.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>

#define PARALLEL_ADDS (10)

int matrix_multiply()
{
  return 1;
}


int main() {

  mutex_t mu;
  mutex_create(&mu);

  int i = 0;
  #pragma omp parallel shared(mu)
  {
    int tid = omp_get_thread_num();

    #pragma omp for schedule(static)
    for(int u = 0; u < PARALLEL_ADDS; u++) {
      mutex_lock(&mu);
      i = i + 1;
      mutex_unlock(&mu);
    }
  }

  printf("i = %d\n", i);


  return 1;
}