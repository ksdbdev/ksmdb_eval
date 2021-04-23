CXX = g++
CXXFLAGS = -g
LINK = $(CXX)

INCLD = -I../../include
LIBS = -L../../lib/linux -lksmdb -lm -lrt -lstdc++ -lpthread

TARGET = backup

OBJS = student.o test.o

all:$(TARGET)

backup:$(OBJS)
	$(LINK) -static -o backup $(OBJS) $(INCLD) $(LIBS)
	rm -rf *.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLD) -c $< -o $@

clean:
	rm -f *.o
	rm -f backup

