# Makefile for Data Structures Programs

CC = gcc
CFLAGS = -Wall -I./src/supporting_data_structures -I./src -I./include

# Tests
TEST_VECTOR = ./tests/test_vectors.c ./src/supporting_data_structures/vector.c
TEST_MIN_HEAP = ./tests/test_heap.c ./src/supporting_data_structures/min_heap.c

# Build index
# TEST_INDEX = ./tests/test_index.c ./src/supporting_data_structures/index.c ./src/hnsw.c

# index_test: $(TEST_INDEX)
# 	$(CC) $(CFLAGS) -o index_test.out $(TEST_INDEX)

vector_test: $(TEST_VECTOR)
	$(CC) $(CFLAGS) -o vector_test.out $(TEST_VECTOR)

min_heap_test: $(TEST_MIN_HEAP)
	$(CC) $(CFLAGS) -o min_heap_test.out $(TEST_MIN_HEAP)