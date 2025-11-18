/**
 * Header files for HNSW implementation. 
 * 
 * Author: Joshua Roberge
 */

#ifndef HNSW_H
#define HNSW_H

#define ARRAY_SIZE 768

#include "supporting_data_structures/vector.h"


typedef struct HNSW_Node {
    int id;
    float *vector;
    int max_layer;
    char* embedding_text;
    HNSW_Node** connections;
} HNSW_Node;

typedef struct HNSW_INDEX {
    int M;
    int M_max;
    int ef_construction;
    int vector_dim;
    float ml;
    int graph_entry_point;
    Vector* nodes;
    int max_layer;
    int size;
} HNSW_INDEX;


#endif