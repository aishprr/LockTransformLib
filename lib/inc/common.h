#ifndef _COMMON_H
#define _COMMON_H

#include <CycleTimer.h>

#define SUCCESS_RETVAL (0)
#define FAILURE_RETVAL (-1)
#define MAX(a,b) (a < b? (b) : (a))

#ifdef DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)
#else
#define dbg_printf(...)
#endif


static inline void log_time_out(double startTime, char *logger) {
  double endTime = CycleTimer::currentSeconds();
  double timeTaken = endTime - startTime;
  printf("%s: Time = %f\n", logger, timeTaken);
}

static inline double log_time_in() {
  return CycleTimer::currentSeconds();
}


#ifdef TIME
#define TIME_OUT(startTime, logger) log_time_out(startTime, logger);
#define TIME_IN log_time_in();
#else
#define TIME_OUT(startTime, logger)
#define TIME_IN (2)
#endif

#endif /* _COMMON_H */