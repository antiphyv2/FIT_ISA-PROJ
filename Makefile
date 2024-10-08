PROJ=isa-top
CFLAGS=-std=c++20
CFLAGS_TESTING = -std=c++20 -DDEBUG_MODE
CC=g++
RM=rm -f

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

$(PROJ) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpcap -pthread -lncurses

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(CC) $(CFLAGS_TESTING) -o $(PROJ) $(SRCS) -lpcap -pthread -lncurses

clean :
	$(RM) *.o $(PROJ) 
