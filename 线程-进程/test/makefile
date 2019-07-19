CC = g++
XX = g++
CFLAG5 = -Wall -O -g
TARGET = test
LIB = -lpthread

%.o:%.cpp
	$(XX) $(CFLAG5) -c $<  -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET):$(OBJS)
	$(XX) $(OBJS)  $(LIB) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)