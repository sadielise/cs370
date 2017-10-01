# Makefile for PA1

# List of files
C_SRCS		= PA1.c
C_OBJS		= PA1.o

OBJS		= ${C_OBJS} 
EXE	        = PA1.out

# Compiler and loader commands and flags
GCC	= gcc
GCC_FLAGS	= -g -std=c99 -Wall -c
LD_FLAGS	= -g -std=c99 -Wall

# Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<

# Target is the executable
default: $(OBJS)	
	$(GCC) $(LD_FLAGS) $(OBJS) -o $(EXE)

# Clean up the directory
clean:
	rm -f *.o *~ $(EXE) 

