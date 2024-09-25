PROJ=isa-top
CFLAGS=-std=c++20
CFLAGS_TESTING = -std=c++20 -DDEBUG_MODE
CC=g++
RM=rm -f

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

$(PROJ) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpcap

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(CC) $(CFLAGS_TESTING) -o $(PROJ) $(SRCS) -lpcap

clean :
	$(RM) *.o $(PROJ) 
