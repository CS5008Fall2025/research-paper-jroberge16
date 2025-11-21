# Makefile for Data Structures Programs

CC = gcc
CFLAGS = -Wall
CFLAGS = -Wall -I./src/supporting_data_structures -I./src -I./include

# Tests
TEST_VECTOR = ./tests/test_vectors.c ./src/supporting_data_structures/vector.c

# Build index
TEST_INDEX = ./tests/test_index.c ./src/hnsw.c ./src/distance.c ./src/supporting_data_structures/vector.c ./src/supporting_data_structures/min_heap.c
TEST_DISTANCE = ./tests/test_distance.c ./src/distance.c
TEST_MIN_HEAP = ./tests/test_heap.c ./src/supporting_data_structures/min_heap.c
TEST_HASH_MAP = ./tests/test_hash.c ./src/supporting_data_structures/hash.c
TEST_ADJ_LIST = ./tests/test_adj.c ./src/supporting_data_structures/adj_list.c



all: index_test vector_test distance_test min_heap_test


# tests executables
index_test: $(TEST_INDEX)
	$(CC) $(CFLAGS) -o index_test $(TEST_INDEX) -lm

vector_test: $(TEST_VECTOR)
	$(CC) $(CFLAGS) -o vector_test.out $(TEST_VECTOR)

distance_test: $(TEST_DISTANCE)
	$(CC) $(CFLAGS) -o distance_test.out $(TEST_DISTANCE) -lm

min_heap_test: $(TEST_MIN_HEAP)
	$(CC) $(CFLAGS) -o min_heap_test.out $(TEST_MIN_HEAP)

hash_test:$(TEST_MIN_HASH)
	$(CC) $(CFLAGS) -o hash_test.out $(TEST_HASH_MAP)

adj_list_test: $(TEST_ADJ_LIST)
	$(CC) $(CFLAGS) -o adj_list_test.out $(TEST_ADJ_LIST)

priority_queue_test: ./tests/test_priority_que.c ./src/supporting_data_structures/priority_que.c
	$(CC) $(CFLAGS) -o priority_queue_test.out ./tests/test_priority_que.c ./src/supporting_data_structures/priority_que.c

test_neighbores: ./tests/test_neighbores.c ./src/neighbores.c ./src/supporting_data_structures/vector.c
	$(CC) $(CFLAGS) -o test_neighbores.out ./tests/test_neighbores.c ./src/neighbores.c ./src/supporting_data_structures/vector.c



clean:
	rm -f index_test.out vector_test.out distance_test.out min_heap_test.out hash_test.out adj_list_test.out priority_queue_test.out test_neighbores.out