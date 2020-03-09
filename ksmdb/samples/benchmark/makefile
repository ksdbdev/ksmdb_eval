CXX = g++
CXXFLAGS = -g
LINK = $(CXX)

INCLD = -I../../include
LIBS = -L../../lib/linux -lksmdb -lm -lrt -lstdc++ -lpthread -lboost_system -lboost_thread

TARGET = perf

OBJS = perf.o testperf.o

all:$(TARGET)

perf:$(OBJS)
	$(LINK) -static -o perf $(OBJS) $(INCLD) $(LIBS)
	rm -rf *.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLD) -c $< -o $@

clean:
	rm -f *.o
	rm -f perf

