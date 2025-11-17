#ifndef VECTOR_H
#define VECTOR_H
//source: https://www.educative.io/answers/how-to-implement-a-vector-in-c
#include <stdlib.h> 
#include <string.h>
#define SCALE_FACTOR 1.25

typedef struct {
    void *items;
    int capacity;
    int count;
    size_t single_element_size;
} Vector;

Vector* create_vector(size_t element_size, int initial_capacity);
void free_vector(Vector* vector);
void append_vector_element(Vector* vector, const void *value);
void insert_vector_element(Vector* vector, size_t index, const void *value);
void* remove_vector_element(Vector* vector, size_t index);
void set_vector_element(Vector* vector, size_t index, const void *value);
void* pop_vector_element(Vector* vector);


#endif