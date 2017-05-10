#!/bin/bash

#first the variable load test
make clean
extend=$(date +"%S_%M_%H_%d")
mkdir logs_${extend}
ORIG_PWD=$(pwd)

make M=rtm T=1
cd user/tests
touch $ORIG_PWD/logs_${extend}/rtm_threadvar_small.txt

for i in {2..10}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/rtm_threadvar_small.txt
done


for i in {2..10}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/rtm_threadvar_small.txt
done
