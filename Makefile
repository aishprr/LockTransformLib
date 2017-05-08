ROOT=$(shell pwd)
INC=$(ROOT)/lib/inc
MUTEXDIR=$(ROOT)/lib/mutex
TESTDIR=$(ROOT)/user/tests

CXX=g++
CXXFLAGS=-I$(INC) -O1 -Wall -mrtm -fopenmp -DRUN_MIC -offload-attribute-target=mic

OBJS=$(MUTEXDIR)/mutex_spin.o\

PRES_OBJS=$()
			
TESTS=$(TESTDIR)/test1

rtm = $(if $(filter ${M},rtm),MUTEX_TRANSACTION_RTM, )
spin = $(if $(filter ${M},spin),MUTEX_SPIN, )
qvol = $(if $(filter ${M},qvol),MUTEX_QUEUE_VOL, )
qflush = $(if $(filter ${M},qflush),MUTEX_QUEUE_FLUSH, )
mcs = $(if $(filter ${M},mcs),MUTEX_MCS_TICKET, )
hle = $(if $(filter ${M},mcs),MUTEX_TRANSACTION_HLE, )

myield = $(if $(filter ${ML},myield),-D YIELD_LOOP, )
mprop = $(if $(filter ${ML},mprop),-D PROP_BACKOFF_LOOP, )
mexp = $(if $(filter ${ML},mexp),-D EXP_BACKOFF_LOOP, )

time = $(if $(filter ${T},1),-D TIME, )

# first clean, then the object files and then the tests
all: clean $(OBJS) $(TESTS)

includes = $(wildcard $(INC)/*.h)


%: %.cpp ${includes} $(OBJS)
	$(CXX) $(CXXFLAGS) -std=c++11 $(OBJS) $< -o $@

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -D $(rtm) $(spin) $(qvol) $(qflush) $(mcs) $(hle) \
	$(myield) $(mprop) $(mexp) $(time) -c -o $@ $<

%.o: %.S
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)