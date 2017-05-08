ROOT=$(shell pwd)
INC=$(ROOT)/lib/inc
MUTEXDIR=$(ROOT)/lib/mutex
TESTDIR=$(ROOT)/user/tests

CXX=g++
CXXFLAGS=-I$(INC) -O1 -Wall -mrtm -fopenmp -DRUN_MIC -offload-attribute-target=mic

###CPPFLAGS=-std=c++11 -fpic -m64 -O3 -Wall -openmp -offload-attribute-target=mic -DRUN_MIC
###CFLAGS=-c -fpic -Wall -m64 -O3 -openmp -offload-attribute-target=mic -DRUN_MIC
###INCFLAGS=-I$(INC)

OBJS=$(MUTEXDIR)/mutex_transaction_rtm.o\

PRES_OBJS=$()
			
TESTS=$(TESTDIR)/test1

rtm = $(if $(filter ${M},rtm),MUTEX_TRANSACTION_RTM, )
spin = $(if $(filter ${M},spin),MUTEX_SPIN, )
qvol = $(if $(filter ${M},qvol),MUTEX_QUEUE_VOL, )
qflush = $(if $(filter ${M},qflush),MUTEX_QUEUE_FLUSH, )
mcs = $(if $(filter ${M},mcs),MUTEX_MCS_TICKET, )
hle = $(if $(filter ${M},mcs),MUTEX_TRANSACTION_HLE, )

#HEADERS=$(INC)/mcs_hybrid_lock.h $(INC)/mcs_queue_lock.h $(INC)/mcs_ticket_lock.h $(INC)/tts_lock.h
# first clean, then the object files and then the tests
all: clean $(OBJS) $(TESTS)

includes = $(wildcard $(INC)/*.h)


%: %.cpp ${includes} $(OBJS)
	$(CXX) $(CXXFLAGS) -std=c++11 $(OBJS) $< -o $@

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -D $(rtm) $(spin) $(qvol) $(qflush) $(mcs) $(hle) -c -o $@ $<

%.o: %.S
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)