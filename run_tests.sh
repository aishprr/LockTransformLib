#!/bin/bash

TEST_THREADS=$1

JOBNAME=$PBS_JOBID
cd $PBS_O_WORKDIR
PATH=$PATH:$PBS_O_PATH

mkdir -p logs.$JOBNAME

cd user/tests
./test_ll_fine > $PBS_O_WORKDIR/logs.$JOBNAME/log.txt
