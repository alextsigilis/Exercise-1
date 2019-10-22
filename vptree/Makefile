# ####################################################################
#
#			   C/C++ Makefile
#
# Author: Dimitris Floros <fcdimitr@auth.gr>
#
# Adapted from
#  http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# ####################################################################
#
# 'make'        build executable file 'main'
# 'make lib'	build the libraries .a
# 'make clean'  removes all .o and executable files
#

# define the shell to bash
SHELL := /bin/bash

# define the C/C++ compiler to use,default here is clang
CC = gcc

# define compile-time flags
CFLAGS = -O0 -Wall -g -fsanitize=address

# define any directories containing header files
INCLUDES = inc

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib specify
#   their path using -Lpath, something like:
LDFLAGS =

# define any libraries to link into executable:
#   To ling libusb-1.0 :
#   LIBS = -lusb-1.0
LIBS =

# define the source file for the library
SRC = vptree

# define the different possible executables
TYPES = sequential

# define the executable file  name
MAIN = main

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above
#

# call everytime
.PRECIOUS: %.a

all: $(addprefix $(MAIN)_, $(TYPES))

lib: $(addsuffix .a, $(addprefix lib/$(SRC)_, $(TYPES)))

$(MAIN)_%: $(MAIN).c lib/$(SRC)_%.a
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file)

$(addsuffix .a, $(addprefix lib/$(SRC)_, $(TYPES))): $(addsuffix .o, $(addprefix lib/$(SRC)_, $(TYPES)))
	ar rcs $@ $<

# (see the gnu make manual section about automatic variables)
$(addsuffix .o, $(addprefix lib/$(SRC)_, $(TYPES))): $(addsuffix .c, $(addprefix src/$(SRC)_, $(TYPES)))
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ -c $<

clean:
	$(RM) lib/*.o *~ $(addprefix $(MAIN)_, $(TYPES)) lib/*.a
