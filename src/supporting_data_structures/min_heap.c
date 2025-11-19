#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "vector.h"
#include "min_heap.h"


// Supporting Functions
int __get_parent(int i){
    return (i-1)/2;
}

int __get_left_child(int i){
    return (2*i + 1);
}

int __get_right_child(int i){
    return(2*i +2);
}

HeapType peak_heap(MinHeap* heap){
    return heap->arr[0];
}

MinHeap* initialize_heap(int capacity){
    
    MinHeap* minheap = (MinHeap*)calloc(1, sizeof(MinHeap));
    if (minheap == NULL){
        perror("Failed to allocate min heap");
        exit(EXIT_FAILURE);
    }
    minheap->arr = (HeapType*) calloc (capacity, sizeof(HeapType));
    if (minheap->arr == NULL){
        perror("Failed to allocate min heap array");
        exit(EXIT_FAILURE);
    }

    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}

void free_heap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

void increase_capacity(MinHeap* min_heap){
    int new_cap = (int)(min_heap->capacity * CAPACITY_INCREASE_FACTOR);
    HeapType* new_arr = (HeapType*)realloc(min_heap->arr, new_cap * sizeof(HeapType));
    if (new_arr == NULL) {
        perror("Failed to reallocate min heap array");
        exit(EXIT_FAILURE);
    }
    min_heap->arr = new_arr;
    min_heap->capacity = new_cap;
}



MinHeap* insert_heap_value(MinHeap* min_heap, HeapType value){
    if (min_heap->size == min_heap->capacity) {
        increase_capacity(min_heap);
    }

    min_heap->size++;
    min_heap->arr[min_heap->size - 1] = value;
    int curr = min_heap->size - 1;

    while (curr > 0 && min_heap->arr[__get_parent(curr)] > min_heap->arr[curr]) {
        int temp = min_heap->arr[__get_parent(curr)];
        min_heap->arr[__get_parent(curr)] = min_heap->arr[curr];
        min_heap->arr[curr] = temp;
        curr = __get_parent(curr);
    }
    return min_heap; 
}

MinHeap* heapify(MinHeap* heap, int index) {

    if (heap->size <= 1)
        return heap;
    
    int left = __get_left_child(index); 
    int right = __get_right_child(index); 

    int smallest = index; 
    
    if (left < heap->size && heap->arr[left] < heap->arr[index]) 
        smallest = left; 

    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) 
        smallest = right; 

    if (smallest != index) 
    { 
        HeapType temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        heap = heapify(heap, smallest); 
    }

    return heap;
}
MinHeap* delete_element(MinHeap* heap, int index) {
    heap->arr[index] = peak_heap(heap) - 1;
    
    int curr = index;
    while (curr > 0 && heap->arr[__get_parent(curr)] > heap->arr[curr]) {
        HeapType temp = heap->arr[__get_parent(curr)];
        heap->arr[__get_parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        curr = __get_parent(curr);
    }

    pop_heap(heap);
    return heap;
}

HeapType pop_heap(MinHeap* heap){
    if (!heap || heap->size == 0){
        return HEAP_TYPE_MAX;
    }
    HeapType min = heap->arr[0];
    int size = heap->size;
    int last_element = heap->arr[size-1];
    
    heap->arr[0] = last_element;

    heap->size--;
    size--;
    heap = heapify(heap, 0);
    return min;

}
