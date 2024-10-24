# Define the compiler and flags
CC = gcc
CFLAGS = -fopenmp -O3 -march=native -ftree-vectorize

# Targets and their rules
all: conv_parallel conv_sequential

conv_parallel: conv_parallel.c
	$(CC) $(CFLAGS) -o conv_parallel conv_parallel.c

conv_sequential: conv_sequential.c
	$(CC) -o conv_sequential conv_sequential.c

# Clean up compiled files
clean:
	rm -f conv_parallel conv_sequential
