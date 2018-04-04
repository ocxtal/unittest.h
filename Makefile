
CC = gcc
CFLAGS = -Wall -O3 -std=c11

all: example example2

example example2:
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	rm -f example example2
