CC = gcc-9

CFLAGS = -O3 -Wall -g  -fopenmp -fcilkplus

INC = -Iinc/
TYPES = sequential pthreads openmp cilk

SHELL := /bin/bash

SRC = vptree

MAIN = main

all: $(addprefix $(MAIN)_, $(TYPES))

$(MAIN)_%: $(MAIN).c lib/$(SRC)_%.a
	$(CC) $(CFLAGS) $(INC) -o $@ $^ libcilkrts.a
	rm -rf *.dSYM

lib: $(addsuffix .a, $(addprefix lib/$(SRC)_, $(TYPES)))


lib/%.a: lib/%.o
	ar rcs $@ $<

lib/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf *.dSYM lib/* *~ $(addprefix $(MAIN)_, $(TYPES))
