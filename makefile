# Makefile for Data Structures Programs

CC = gcc
CFLAGS = -Wall
CFLAGS = -Wall -I./src/supporting_data_structures -I./src -I./include
# Tests
TEST_VECTOR = ./tests/test_vectors.c ./src/supporting_data_structures/vector.c

vector_test: $(TEST_VECTOR)
	$(CC) $(CFLAGS) -o vector_test $(TEST_VECTOR)


