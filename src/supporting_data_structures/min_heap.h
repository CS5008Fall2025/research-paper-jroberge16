#ifndef MIN_HEAP_H
#define MIN_HEAP_H
//source: https://www.digitalocean.com/community/tutorials/min-heap-binary-tree
#define CAPACITY_INCREASE_FACTOR 1.5
#include <float.h>

#define HEAP_TYPE_MAX FLT_MAX

typedef float HeapType; 

typedef struct{
    HeapType* arr;
    int size;
    int capacity;
} MinHeap;


HeapType peak_heap(MinHeap* heap);
MinHeap* initialize_heap(int capacity);
void free_heap(MinHeap* heap);
void increase_capacity(MinHeap* min_heap);
MinHeap* insert_heap_value(MinHeap* min_heap, HeapType value);
MinHeap* heapify(MinHeap* heap, int index);
MinHeap* delete_element(MinHeap* heap, int index);
HeapType pop_heap(MinHeap* heap);

#endif