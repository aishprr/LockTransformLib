#include "../../lib/mutex/mutex_type.h"
#include "../structures/ll_coarse_grained.h"
#include "../../lib/inc/common.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>
#include <unistd.h>

#define OUT_STRING "Final time taken"

int compare_int(void *adata, void *bdata) {
  return ((long)(adata) - (long)(bdata));
}

int main(int argc, char *argv[]) {

  ll_coarse l;
  ll_coarse_init(&l, compare_int);

  int in_par = 0;
  int def_par = 1;
  char opt;
  
  while ((opt = getopt(argc, argv, "p:")) != -1) {
    switch (opt) {
      case 'p': 
          in_par = atoi(optarg);
          break;
      default:
          fprintf(stderr, "Usage: %s -p par_count\n", argv[0]);
          exit(EXIT_FAILURE);
      }
  }

  int fin_par = MAX(in_par, def_par);
  printf("Threads = %d\n", fin_par);

  double startTime = CycleTimer::currentSeconds();

  #pragma omp parallel for num_threads(fin_par)
  for(int u = 0; u < fin_par; u++)
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