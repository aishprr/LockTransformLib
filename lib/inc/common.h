#ifndef _COMMON_H
#define _COMMON_H

#include <CycleTimer.h>

#define SUCCESS_RETVAL (0)
#define FAILURE_RETVAL (-1)

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
#define TIME_IN
#endif

#endif /* _COMMON_H */