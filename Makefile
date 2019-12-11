CXX=g++
RM=rm -f
SRC_DIR=src
CPPFLAGS=-O3 -DNDEBUG -std=gnu++1z -I$(SRC_DIR)
LDFLAGS=-O3 -DNDEBUG -std=gnu++1z

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
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