ROOT=$(shell pwd)
INC=$(ROOT)/lib/inc
MUTEXDIR=$(ROOT)/lib/mutex
TESTDIR=$(ROOT)/user/tests

CXX=g++
CXXFLAGS=-I$(INC) -O1 -Wall -openmp -DRUN_MIC -offload-attribute-target=mic

#CPPFLAGS=-std=c++11 -fpic -m64 -O3 -Wall -openmp -offload-attribute-target=mic -DRUN_MIC
#CFLAGS=-c -fpic -Wall -m64 -O3 -openmp -offload-attribute-target=mic -DRUN_MIC
#INCFLAGS=-I$(INC)


OBJS=$(MUTEXDIR)/mutex_mcs_ticket.o\
	$(MUTEXDIR)/mutex_queue.o $(MUTEXDIR)/mutex_spin.o\
	$(MUTEXDIR)/mutex_transaction_1.o

TESTS=$(TESTDIR)/test1.cpp

#HEADERS=$(INC)/mcs_hybrid_lock.h $(INC)/mcs_queue_lock.h $(INC)/mcs_ticket_lock.h $(INC)/tts_lock.h
all: clean $(OBJS) $(TESTS)

includes = $(wildcard $(INC)/*.h)


%.o: %.cpp ${includes}
	$(CXX) $(CXXFLAGS) -std=c++11 $(OBJS) $< -o $@

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.S
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)