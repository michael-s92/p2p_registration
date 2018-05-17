PROG = app
CC = g++
CFLAGS = -Wall -ansi

$(PROG): main.o ClientSocket.o ComputeHash.o
	$(CC) -o $@ $^ -lssl -lcrypto -pthread
	
*.o: *.cpp ClientSocket.hpp ComputeHash.h Constants.h
	$(CC) -c $(CFLAGS) $<


.PHONY: clean

clean:
	rm -f *.o $(PROG) *~ hash.bin
