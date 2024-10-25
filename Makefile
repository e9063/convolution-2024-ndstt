# Define the compiler and flags
CC = gcc
CFLAGS = -fopenmp

# Targets and their rules
all: conv_parallel conv_sequential benchmark

conv_parallel: conv_parallel.c
	$(CC) $(CFLAGS) -o conv_parallel conv_parallel.c

conv_sequential: conv_sequential.c
	$(CC) -o conv_sequential conv_sequential.c

benchmark: benchmark.c
	$(CC) $(CFLAGS) -o benchmark benchmark.c

# Clean up compiled files
clean:
	rm -f conv_parallel conv_sequential
