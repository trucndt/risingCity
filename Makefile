CXX=g++
RM=rm -f
CPPFLAGS=-O3 -DNDEBUG -std=gnu++1z -I$(shell pwd)
LDFLAGS=-O3 -DNDEBUG -std=gnu++1z

SRCS=main.cpp RBT.cpp NodeBase.cpp Simulator.cpp MinHeap.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: risingCity

risingCity: $(OBJS)
	$(CXX) $(LDFLAGS) -o risingCity $(OBJS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) risingCity
	$(RM) *~ .depend

distclean: clean

include .depend