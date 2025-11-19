#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "vector.h"
#include "distance.h"
#include "min_heap.h"
#include "hnsw.h"



void test_index(){
    HNSW_INDEX* index = create_hnsw_index(1, 2, 3.0f, 4, "euclidean", 5, 6, 7);
    assert(index != NULL);
    assert(index->M == 1);
    assert(index->ef_construction == 2);
    assert(index->ml == 3.0f);
    assert(index->vector_dim == 4);
    assert(index->max_layer == 6);
    assert(index->size == 0);
    assert(index->M_max == 7);
    assert(index->distance_function != NULL);
    printf("\t✅ HNSW Index Creation\n");
}


int main() {
    printf("🧪 Testing HNSW Index\n");
    test_index();
    printf("🥳 ALL TESTS PASSED\n");
    return 0;
}