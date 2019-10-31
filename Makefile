CC = gcc

CFLAGS = -O0 -Wall -g -fsanitize=address

INC = -Iinc/

TYPES = sequential

SHELL := /bin/bash

SRC = vptree

MAIN = tester

all: $(addprefix $(MAIN)_, $(TYPES))

$(MAIN)_%: $(MAIN).c lib/$(SRC)_%.a
	$(CC) $(CFLAGS) $(INC) -o $@ $^

lib: $(addsuffix .a, $(addprefix lib/$(SRC)_, $(TYPES)))


lib/%.a: lib/%.o
	ar rcs $@ $<

lib/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf *.dSYM lib/* *~ $(addprefix $(MAIN)_, $(TYPES))
