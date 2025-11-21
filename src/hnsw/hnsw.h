/**
 * Header files for HNSW implementation. 
 * 
 * Author: Joshua Roberge
 */

#ifndef HNSW_H
#define HNSW_H

#define ARRAY_SIZE 768

#include "supporting_data_structures/vector.h"
#include "distance.h"

typedef struct HNSW_Node HashNode; 


typedef struct ConnectionList {
    int *connections;
    int count;
    int capacity;
} ConnectionList;


typedef struct HNSW_Node {
    int id;
    float *vector;
    int max_layer;
    ConnectionList* connections;
} HNSW_Node;

typedef struct HNSW_INDEX {
    Vector* nodes;
    int M;
    int M_max;
    int ef_construction;
    int vector_dim;
    float ml;
    int graph_entry_point;
    int max_layer;
    int size;
    int max_node_id;
    int Mmax;
    int Mmax0;   
    DistanceFunction distance_function;
} HNSW_INDEX;


#endif