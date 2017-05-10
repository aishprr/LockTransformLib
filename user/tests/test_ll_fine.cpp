#include "../../lib/mutex/mutex_type.h"
#include "../structures/ll_fine_grained.h"
#include "../../lib/inc/common.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>
#include <unistd.h>

#define OUT_STRING "Final time taken"
#define HYPERTHREADS (16)

int compare_int(void *adata, void *bdata) {
  return ((long)(adata) - (long)(bdata));
}

int main(int argc, char *argv[]) {

  
  ll_fine l;
  ll_fine_init(&l, compare_int);

  int in_par = 0;
  int def_par = 1;
  char opt;
  dbg_printf("argc = %d\n", argc);

  while ((opt = getopt(argc, argv, "p:")) != -1) {
    switch (opt) {
      case 'p': 
          dbg_printf("value = %s\n", optarg);
          in_par = atoi(optarg);
          break;
      default:
          fprintf(stderr, "Usage: %s -p par_count\n", argv[0]);
          exit(EXIT_FAILURE);
      }
  }

  int fin_par = HYPERTHREADS * MAX(in_par, def_par);
  dbg_printf("fin par = %d\n", fin_par);

#ifdef TOT_TIME
  double startTime = CycleTimer::currentSeconds();
#endif

  #pragma omp parallel for schedule(static,1)
  for(int u = 0; u < fin_par; u++)
  {
    ll_fine_node *node = (ll_fine_node *)malloc(sizeof(ll_fine_node));
    ll_fine_insert(&l, node, (void *)(0));
  }
#ifdef TOT_TIME
  double endTime = CycleTimer::currentSeconds();
  double timeTaken = endTime - startTime;
  printf("%f\n", timeTaken);
#endif
  int a = ll_fine_count_elems(&l);
  if (a != fin_par) {
    printf("Failed Total nodes = %d, should be %d\n", a, fin_par);
  }
  
}
