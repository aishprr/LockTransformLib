#!/bin/bash

#first the variable load test
make clean
extend=$(date +"%M_%H_%d")
mkdir logs_${extend}_llcoarse
ORIG_PWD=$(pwd)

#### MUTEX_RTM ####

make M=rtm TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/rtm_tot_llcoarse.txt

echo "#### RTM [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/rtm_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/rtm_tot_llcoarse.txt
done

#### MUTEX_SPIN_TYPE always spin ####
cd $ORIG_PWD
make M=spin TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/spin_alw_tot_llcoarse.txt

echo "#### Spin *always* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/spin_alw_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/spin_alw_tot_llcoarse.txt
done

#### MUTEX_SPIN_TYPE yield in between ####
cd $ORIG_PWD
make M=spin ML=myield TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/spin_yield_tot_llcoarse.txt

echo "#### Spin *yield* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/spin_yield_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/spin_yield_tot_llcoarse.txt
done


#### MUTEX_SPIN_TYPE exp backoff in between ####
cd $ORIG_PWD
make M=spin ML=mexp TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/spin_exp_tot_llcoarse.txt

echo "#### Spin *exp* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/spin_exp_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/spin_exp_tot_llcoarse.txt
done

#### MUTEX_QVOL_TYPE always spin ####
cd $ORIG_PWD
make M=qvol TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/qvol_alw_tot_llcoarse.txt

echo "#### qvol *always* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/qvol_alw_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/qvol_alw_tot_llcoarse.txt
done

#### MUTEX_QVOL_TYPE yield in between ####
cd $ORIG_PWD
make M=qvol ML=myield TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/qvol_yield_tot_llcoarse.txt

echo "#### qvol *yield* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/qvol_yield_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/qvol_yield_tot_llcoarse.txt
done

#### MUTEX_QVOL_TYPE exp backoff in between ####
cd $ORIG_PWD
make M=qvol ML=mexp TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/qvol_exp_tot_llcoarse.txt

echo "#### qvol *exp* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/qvol_exp_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/qvol_exp_tot_llcoarse.txt
done

#### MUTEX_QVOL_TYPE prop backoff in between ####
cd $ORIG_PWD
make M=qvol ML=mprop TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_llcoarse/qvol_prop_tot_llcoarse.txt

echo "#### qvol *prop* [1*16, 15*16] threads, Small critical \
./test_ll_coarse -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_llcoarse/qvol_prop_tot_llcoarse.txt

for i in {1..15}
do
  # only run with the small critical section version with rtm
  ./test_ll_coarse -p ${i} >> $ORIG_PWD/logs_${extend}_llcoarse/qvol_prop_tot_llcoarse.txt
done


