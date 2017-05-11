#!/bin/bash

#first the variable load test
make clean
extend=$(date +"%M_%H_%d")
mkdir logs_${extend}_threadvar
ORIG_PWD=$(pwd)

#### MUTEX_RTM ####

make M=rtm TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt

echo "#### RTM [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt
done

echo "#### RTM [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt
done

echo "#### RTM [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/rtm_tot_threadvar.txt
done

#### MUTEX_SPIN_TYPE always spin ####
cd $ORIG_PWD
make M=spin TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt

echo "#### Spin *always* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt
done

echo "#### Spin *always* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt
done

echo "#### Spin *always* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/spin_alw_tot_threadvar.txt
done

#### MUTEX_SPIN_TYPE yield in between ####
cd $ORIG_PWD
make M=spin ML=myield TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt

echo "#### Spin *yield* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt
done

echo "#### Spin *yield* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt
done

echo "#### Spin *yield* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/spin_yield_tot_threadvar.txt
done

#### MUTEX_SPIN_TYPE exp backoff in between ####
cd $ORIG_PWD
make M=spin ML=mexp TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt

echo "#### Spin *exp* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt
done

echo "#### Spin *exp* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt
done

echo "#### Spin *exp* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/spin_exp_tot_threadvar.txt
done

#### MUTEX_QVOL_TYPE always spin ####
cd $ORIG_PWD
make M=qvol TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt

echo "#### qvol *always* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt
done

echo "#### qvol *always* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt
done

echo "#### qvol *always* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/qvol_alw_tot_threadvar.txt
done

#### MUTEX_QVOL_TYPE yield in between ####
cd $ORIG_PWD
make M=qvol ML=myield TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt

echo "#### qvol *yield* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt
done

echo "#### qvol *yield* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt
done

echo "#### qvol *yield* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/qvol_yield_tot_threadvar.txt
done

#### MUTEX_QVOL_TYPE exp backoff in between ####
cd $ORIG_PWD
make M=qvol ML=mexp TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt

echo "#### qvol *exp* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt
done

echo "#### qvol *exp* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt
done

echo "#### qvol *exp* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/qvol_exp_tot_threadvar.txt
done

#### MUTEX_QVOL_TYPE prop backoff in between ####
cd $ORIG_PWD
make M=qvol ML=mprop TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt

echo "#### qvol *prop* [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt
done

echo "#### qvol *prop* [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt
done

echo "#### qvol *prop* [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/qvol_prop_tot_threadvar.txt
done


#### omp critical section ####
cd $ORIG_PWD
make M=spin O=1 TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt

echo "#### ompcrit [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt
done

echo "#### ompcrit [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt
done

echo "#### ompcrit [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt

for i in {1..30}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_threadvar/ompcrit_tot_threadvar.txt
done
