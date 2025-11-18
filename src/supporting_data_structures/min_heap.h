#ifndef MIN_HEAP_H
#define MIN_HEAP_H
//source: https://www.digitalocean.com/community/tutorials/min-heap-binary-tree

typedef float HeapType; 
 
typedef struct{
    HeapType* arr;
    int size;
    int capacity;
} MinHeap;

#endif