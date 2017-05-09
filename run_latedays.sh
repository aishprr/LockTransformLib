#!/bin/bash

# First argument is the maximum number of workers to allocate for your job; the
# cluster will reserve that many computers, plus one for the master, for the
# duration of the job.
TEST_THREADS=$1

# Second argument is the trace to run.

qsub -F "$TEST_THREADS" latedays.qsub
