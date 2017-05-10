#include "../../lib/mutex/mutex_type.h"
#include "../../lib/inc/common.h"
#include "../structures/ll_fine_grained.h"
#include "../structures/ll_coarse_grained.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstddef>
#include <sched.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  mutex_t mu;
  mutex_create(&mu);

  int in_par = 0;
  int def_par = 1;
  int in_crit = 0;
  int def_crit = 0;
  int operate = 0;
  char opt;
  printf("argc = %d\n", argc);

  // p is for the how many parallel threads to run this on
  // c is how many loops to wait for inside critical section
  // o is whether to increment in each of the above wait loops
  // Compile with USE_OMP_CRIT to run with the open mp implementation
  // Compile without USE_OMP_CRIT and with different types of mutexes to measure

  while ((opt = getopt(argc, argv, "p:c:o")) != -1) {
    switch (opt) {
      case 'p': 
          printf("pvalue = %s\n", optarg);
          in_par = atoi(optarg);
          break;
      case 'c': 
          printf("cvalue = %s\n", optarg);
          in_crit = atoi(optarg);
          break;
      case 'o': 
          printf("o flag passed\n");
          operate = 1;
          break;
      default:
          fprintf(stderr, "Usage: %s -p par_count -c crit_count\n", argv[0]);
          exit(EXIT_FAILURE);
      }
  }

  int fin_par = MAX(in_par, def_par);
  int fin_crit = MAX(in_crit, def_crit);
  printf("fin par = %d, fin crit = %d\n", fin_par, fin_crit);

  int i = 0;
  #pragma omp parallel for num_threads(fin_par)
  for(int u = 0; u < fin_par; u++)
  {
    int tid = omp_get_thread_num();
    int cpu_num = sched_getcpu();
    printf("thread %d on CPU %d\n", tid, cpu_num);
  
    printf("thread number inside %d\n", tid);
#ifdef USE_OMP_CRIT
    #pragma omp critical
    {
#else
    mutex_lock(&mu);
#endif
    i++;
    for(int k = 0; k < fin_crit; k++) {
      if(operate) {
        // just operate on i multiple times in the same loop
        i++;
      }
    }
#ifdef USE_OMP_CRIT
    }
#else
    mutex_unlock(&mu);
#endif
  }

  printf("i = %d\n", i);

  return 1;
}
