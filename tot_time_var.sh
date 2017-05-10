#!/bin/bash

#first the variable load test
make clean
extend=$(date +"%M_%H_%d")
mkdir logs_${extend}
ORIG_PWD=$(pwd)

#### MUTEX_RTM ####

make M=rtm TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt

echo "#### RTM [2, 100] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt
done

echo "#### RTM [2, 100] threads, Long critical less activity \
./test_variable_critical -p tcount -c 100 ####" >>\
 $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 >> $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt
done

echo "#### RTM [2, 100] threads, Long critical more activity \
./test_variable_critical -p tcount -c 100 -o ####" >>\
 $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 >> $ORIG_PWD/logs_${extend}/rtm_tot_threadvar_small.txt
done

#### MUTEX_SPIN_TYPE always spin ####
cd $ORIG_PWD
make M=spin TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

echo "#### Spin *always* [2, 100] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *always* [2, 100] threads, Long critical less activity \
./test_variable_critical -p tcount -c 100 ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *always* [2, 100] threads, Long critical more activity \
./test_variable_critical -p tcount -c 100 -o ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 -o >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

#### MUTEX_SPIN_TYPE yield in between ####
cd $ORIG_PWD
make M=spin ML=myield TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

echo "#### Spin *yield* [2, 100] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *yield* [2, 100] threads, Long critical less activity \
./test_variable_critical -p tcount -c 100 ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *yield* [2, 100] threads, Long critical more activity \
./test_variable_critical -p tcount -c 100 -o ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 -o >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

#### MUTEX_SPIN_TYPE exp backoff in between ####
cd $ORIG_PWD
make M=spin ML=mexp TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

echo "#### Spin *exp* [2, 100] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *exp* [2, 100] threads, Long critical less activity \
./test_variable_critical -p tcount -c 100 ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

echo "#### Spin *exp* [2, 100] threads, Long critical more activity \
./test_variable_critical -p tcount -c 100 -o ####" >>\
 $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt

for i in {2..100}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 100 -o >> $ORIG_PWD/logs_${extend}/spin_tot_threadvar_small.txt
done

