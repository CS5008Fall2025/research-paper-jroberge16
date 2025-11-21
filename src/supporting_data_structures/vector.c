#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "vector.h"


Vector* create_vector(size_t element_size, int initial_capacity){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL){
        perror("Failed to allocate vector");
        exit(EXIT_FAILURE);
    }
    vector->items = malloc(initial_capacity * element_size);
    if (vector->items == NULL){
        free(vector);
        perror("Failed to allocate item space in vector");
        exit(EXIT_FAILURE);
    }
    vector-> single_element_size = element_size;
    vector->capacity = initial_capacity;
    vector->count = 0;
    return vector;
}

void free_vector(Vector* vector) {
    if (vector != NULL) {
        free(vector->items); // Free the data array
        free(vector); // Free the vector structure
    }
}


void __vector_resize(Vector* vector){
    int new_capacity = (int)(vector->capacity * SCALE_FACTOR);
    void* new_data = realloc(vector->items, new_capacity * vector->single_element_size);
    if (new_data != NULL) {
            vector->items = new_data; // Update the data pointer
            vector->capacity = new_capacity; // Update the capacity
    } else {
        perror("Memory allocation failed during resize.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Appends an element to the end of the vector.
 * 
 * @param vector A pointer to the vector.
 * @param value The value to append.
 * @return 0 if successful, or -1 if memory allocation fails.
 */
void append_vector_element(Vector* vector, const void *value) {
    insert_vector_element(vector, vector->count, value);
}


/**
 * Inserts an element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index at which to insert the element.
 * @param value The value to insert.
 */
void insert_vector_element(Vector* vector, size_t index, const void *value) {
    if (index > vector->count) {
        fprintf(stderr, "Index out of bounds.\n");
        return; // Index is out of bounds
    }
    if (vector->count == vector->capacity) {
        __vector_resize(vector);
    }
    if (index < vector->count) {
        memmove(
            ((char*)vector->items) + (index + 1) * vector->single_element_size,
            ((char*)vector->items) + index * vector->single_element_size,  
            (vector->count - index) * vector->single_element_size       
        );
    }

    memcpy(
        ((char*)vector->items) + index * vector->single_element_size,
        value,
        vector->single_element_size   
    );
    vector->count++;
}

/**
 * Removes the element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index of the element to remove.
 * @return the element removed at index 
 */
void* remove_vector_element(Vector* vector, size_t index) {
    if (index >= vector->count) {
        fprintf(stderr, "Index out of bounds.\n");
        errno = ERANGE;
        return NULL;
    }
    errno = 0;
    
    // Shift elements left using memmove
    if (index < vector->count - 1) {
        memmove(
            ((char*)vector->items) + index * vector->single_element_size,
            ((char*)vector->items) + (index + 1) * vector->single_element_size,
            (vector->count - index - 1) * vector->single_element_size
        );
    }
    vector->count--;
    return NULL;  // Can't return removed value without allocating memory
}

/**
 * Sets the element at the specified index in the vector.
 * 
 * @param vector A pointer to the vector.
 * @param index The index of the element to set.
 * @param value The value to set at the specified index.
 */
void set_vector_element(Vector* vector, size_t index, const void *value) {
    if (index >= vector->count) {
        fprintf(stderr, "Index out of bounds.\n");
        errno = ERANGE;
        return;
    }
    errno = 0;
    memcpy(
        ((char*)vector->items) + index * vector->single_element_size,
        value,
        vector->single_element_size
    );
}

/**
 * Removes and returns the last element of the vector.
 * 
 * @param vector A pointer to the vector.
 * @return The value of the removed element, or -1 if the vector is empty.
 */
void* pop_vector_element(Vector* vector) {
    return remove_vector_element(vector, vector->count - 1); // Remove the last element
}