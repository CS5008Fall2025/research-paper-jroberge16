# Makefile for Data Structures Programs

CC = gcc
CFLAGS = -Wall

# Tests
TEST_AVL = ./test/test_avl.c ./avl/avl.c

.PHONY: all test_avl clean

all: test_avl

test_avl: $(TEST_AVL)
	$(CC) $(CFLAGS) -o test_avl.out $(TEST_AVL)

clean:
	rm -f test_avl.out