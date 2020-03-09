CXX = g++
CXXFLAGS = -g
LINK = $(CXX)

INCLD = -I../../include
LIBS = -L../../lib/linux -lksmdb -lm -lrt -lstdc++ -lpthread -lboost_system -lboost_thread

TARGET = multithread

OBJS = student.o test.o tools.o

all:$(TARGET)

multithread:$(OBJS)
	$(LINK) -static -o multithread $(OBJS) $(INCLD) $(LIBS)
	rm -rf *.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLD) -c $< -o $@

clean:
	rm -f *.o
	rm -f multithread

