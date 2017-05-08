#include "../../lib/mutex/mutex_type.h"
#include "../structures/ll_fine_grained.h"
#include "../../lib/inc/common.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>

#define OUT_STRING "Final time taken"

#define PARALLEL_ADDS (15)

int compare_int(void *adata, void *bdata) {
  return ((long)(adata) - (long)(bdata));
}

int main() {

  double tim = TIME_IN;
  ll_fine l;
  ll_fine_init(&l, compare_int);

  #pragma omp parallel for num_threads(PARALLEL_ADDS)
  for(int u = 0; u < PARALLEL_ADDS; u++)
  {
    ll_fine_node *node = (ll_fine_node *)malloc(sizeof(ll_fine_node));
    ll_fine_insert(&l, node, (void *)(0));
  }
  printf("SUP\n");
  TIME_OUT(tim, OUT_STRING);

}