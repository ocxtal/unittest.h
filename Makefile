
CC = gcc
CFLAGS = -Wall -O3

all: example example2

example example2:
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	rm example example2
