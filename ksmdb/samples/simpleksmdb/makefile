CXX = g++
CXXFLAGS = -g
LINK = $(CXX)

INCLD = -I../../include
LIBS = -L../../lib/linux -lksmdb -lm -lrt -lstdc++ -lpthread -lboost_system -lboost_thread

TARGET = simpleksmdb

OBJS = student.o test.o

all:$(TARGET)

simpleksmdb:$(OBJS)
	$(LINK) -static -o simpleksmdb $(OBJS) $(INCLD) $(LIBS)
	rm -rf *.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLD) -c $< -o $@

clean:
	rm -f *.o
	rm -f simpleksmdb

