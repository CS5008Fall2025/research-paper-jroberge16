#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hnsw.h"
#include "supporting_data_structures/vector.h"
#include "distance.h"
#include "supporting_data_structures/min_heap.h"

HNSW_INDEX* create_hnsw_index(int M, int ef_construction, 
                            float ml, int vector_dim,
                            const char* distance_metric_string,
                             int starting_capacity,
                             int max_layer,
                             int M_max
                        ) {
    
    HNSW_INDEX* index = (HNSW_INDEX*)malloc(sizeof(HNSW_INDEX));
    if (index == NULL){
        perror("Failed to allocate HNSW_INDEX");
        exit(EXIT_FAILURE);
    }
    index->M = M;
    index->ef_construction = ef_construction;
    index->ml = ml;
    index->vector_dim = vector_dim;
    index->distance_function = get_distance_function(distance_metric_string);
    index->nodes = create_vector(sizeof(HNSW_Node), starting_capacity);
    index->max_layer = max_layer;
    index->size = 0;
    index->M_max = M_max;
    index->graph_entry_point = -1;
    return index;
}