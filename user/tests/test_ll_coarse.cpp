#include "../../lib/mutex/mutex_type.h"
#include "../structures/ll_coarse_grained.h"
#include "../../lib/inc/common.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>

#define OUT_STRING "Final time taken"

#define PARALLEL_ADDS (100)

int compare_int(void *adata, void *bdata) {
  return ((long)(adata) - (long)(bdata));
}

int main() {

  double startTime = CycleTimer::currentSeconds();
  ll_coarse l;
  ll_coarse_init(&l, compare_int);

  #pragma omp parallel for num_threads(PARALLEL_ADDS)
  for(int u = 0; u < PARALLEL_ADDS; u++)
  {
    ll_coarse_node *node = (ll_coarse_node *)malloc(sizeof(ll_coarse_node));
    ll_coarse_insert(&l, node, (void *)(0));
  }
  int a = ll_coarse_count_elems(&l);
  printf("Total nodes = %d\n", a);
  double endTime = CycleTimer::currentSeconds();
  double timeTaken = endTime - startTime;
  printf("Total: Time = %f\n", timeTaken);
}