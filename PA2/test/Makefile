# Makefile for PA2

# Compiler and loader commands and flags
GCC	= gcc
GCC_FLAGS	= -g -std=c99 -Wall -c
LD_FLAGS	= -g -std=c99 -Wall

# target for both files
all: expox expoxch

# target for expox
expox: expox.o
	$(GCC) $(LD_FLAGS) -o expox expox.o

# target for expoxch
expoxch: expoxch.o
	$(GCC) $(LD_FLAGS) -o expoxch expoxch.o -lm

# target for expox.o
expox.o: expox.c
	$(GCC) $(GCC_FLAGS) expox.c

# target for expoxch.o
expoxch.o: expoxch.c
	$(GCC) $(GCC_FLAGS) expoxch.c

# Clean up the directory
clean:
	rm -f *.o *~ expox expoxch

