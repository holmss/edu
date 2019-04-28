.PHONY  : all, clean, libload
SRC     = $(wildcard *.c)
HDR     = $(wildcard *.h)
CC      = gcc
CFLAGS  = -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3\
          -Wconversion -Wsign-conversion -Wunreachable-code -fstack-protector
LDFLAGS = -ldl
INCLUDE = -L. -ldyn

all: load linked

clean:
	rm -f $(SRC:%.c=%.o) lib* load linked #*.gcno *.gcda

load: lab05D.o libdyn.so  $(HDR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o load

libdyn.so: Arr.o $(HDR)
	$(CC) $(CFLAGS) -shared -fpic -o $@ $<

linked: libdyn.so lab05S.o $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ lab05S.o

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<