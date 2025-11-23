CC = gcc
CFLAGS = -Wall -I.

# Main
MAIN = trees/main.c trees/avl/avl.c trees/binnary/binnary.c trees/benchmarking/avl_benchmarks.c trees/benchmarking/bench_utils.c trees/benchmarking/bin_benchmarks.c

# Tests
TEST_AVL = test/test_avl.c trees/avl/avl.c
TEST_BINNARY = test/test_binnary.c trees/binnary/binnary.c	

.PHONY: all test_avl test_binnary clean

all: main

main: $(MAIN)
	$(CC) $(CFLAGS) -o main.out $(MAIN) -lrt

test_avl: $(TEST_AVL)
	$(CC) $(CFLAGS) -o test_avl.out $(TEST_AVL)

test_binnary: $(TEST_BINNARY)
	$(CC) $(CFLAGS) -o test_binnary.out $(TEST_BINNARY)

clean:
	rm -f test_avl.out test_binnary.out main.out data/results/*.csv