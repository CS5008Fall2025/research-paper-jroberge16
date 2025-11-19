#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "min_heap.h"

void test_min_heap() {
    MinHeap* heap = initialize_heap(10);
    assert(heap != NULL);
    assert(heap->capacity == 10);
    assert(heap->size == 0);
    printf("\t✅ Heap initialized\n");


    heap = insert_heap_value(heap, 10);
    heap = insert_heap_value(heap, 1);
    heap = insert_heap_value(heap, 5);
    heap = insert_heap_value(heap, 3);
    printf("\t✅ Heap insert\n");

    assert(peak_heap(heap) == 1);
    printf("\t✅ Heap peak\n");


    assert(pop_heap(heap) == 1);
    assert(heap->size == 3);
    printf("\t✅ Heap pop\n");


    heap = delete_element(heap, 0);

    free_heap(heap);
    printf("\t✅ Heap delete\n");
}


int main() {
    printf("🧪 Testing Min Heap Implementation\n");
    test_min_heap();
    printf("🥳 ALL TESTS PASSED\n");
    return 0;
}