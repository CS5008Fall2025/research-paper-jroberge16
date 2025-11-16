/**
 * Header files for HNSW implementation. 
 * 
 * Author: Joshua Roberge
 */

#ifndef HNSW_H
#define HNSW_H

#define ARRAY_SIZE 768



typedef struct HNSW_Node {
    int id;
    float *vector;
    int max_layer;
    char* embedding_text;
    HNSW_Node** connections;
} HNSW_Node;

typedef struct HNSW_Node {
    int M;
    int M_max;
    int ef_construction;
    int vector_dim;
    float ml;
    int graph_entry_point;
    HNSW_Node** nodes;
    int max_size_nodes;
    int max_layer;
    int size;
} HNSW;


#endif