#!/bin/bash

#first the variable load test
make clean
extend=$(date +"%M_%H_%d")
mkdir logs_${extend}_transdropped
ORIG_PWD=$(pwd)

#### MUTEX_RTM ####

make M=rtm MD=1 TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt

echo "#### RTM [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt
done

echo "#### RTM [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt
done

echo "#### RTM [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt
done


echo "#### RTM [1*16, 30*16] threads, Long critical less activity uneven wait \
./test_variable_critical -p tcount -c 10000 - ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 1000 -r >> $ORIG_PWD/logs_${extend}_transdropped/rtm_dropped_transdropped.txt
done

#### MUTEX_RTM__BLAH ####
cd $ORIG_PWD
make M=rtmad MD=1 TT=1
cd user/tests
touch $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt

echo "#### RTMAD [1*16, 30*16] threads, Small critical \
./test_variable_critical -p tcount ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} >> $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt
done

echo "#### RTMAD [1*16, 30*16] threads, Long critical less activity \
./test_variable_critical -p tcount -c 10000 ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 >> $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt
done

echo "#### RTMAD [1*16, 30*16] threads, Long critical more activity \
./test_variable_critical -p tcount -c 10000 -o ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 10000 -o >> $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt
done


echo "#### RTMAD [1*16, 30*16] threads, Long critical less activity uneven wait \
./test_variable_critical -p tcount -c 10000 - ####" >>\
 $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt

for i in {1..5}
do
  # only run with the small critical section version with rtm
  ./test_variable_critical -p ${i} -c 1000 -r >> $ORIG_PWD/logs_${extend}_transdropped/rtmad_dropped_transdropped.txt
done