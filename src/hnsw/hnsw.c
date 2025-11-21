#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hnsw.h"
#include "supporting_data_structures/vector.h"
#include "distance.h"
#include "supporting_data_structures/min_heap.h"
#include "supporting_data_structures/adj_list.h"
#include "neighbores.h"
#include "supporting_data_structures/priority_que.h"



HNSW_INDEX* create_hnsw_index(
    int M, int ef_construction, 
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
    index->Mmax = M;
    index->Mmax0 = M * 2;
    index->ef_construction = ef_construction;
    index->ml = ml;
    index->vector_dim = vector_dim;
    index->distance_function = get_distance_function(distance_metric_string);
    index->nodes = create_vector(sizeof(HNSW_Node), starting_capacity);
    index->max_layer = max_layer;
    index->size = 0;
    index->M_max = M_max;
    index->graph_entry_point = -1;
    index->max_node_id = 0;
    return index;
}

void free_index(HNSW_INDEX* index){
    if(index == NULL) return;

    for(int i = 0; i < index->nodes->count; i++){
        HNSW_Node* node = ((HNSW_Node**)index->nodes->items)[i];
        free(node->vector);
        free(node->connections);
        free(node);
    }
    free_vector(index->nodes);
    free(index);
}


int __select_level_assignment(HNSW_INDEX* index){
    srand(time(NULL));
    float uniform_random = ((float)rand() + 1.0f) / ((float)RAND_MAX + 1.0f);
    int level = (int)(-log(uniform_random) * index->ml);
    return level;
}

void __create_node(HNSW_Node* new_node, int node_id, float* vector, int max_layer, HNSW_INDEX* index){
    new_node->id = node_id;
    new_node->vector = vector;
    new_node->max_layer = max_layer;
    new_node->connections = (HNSW_Node**)malloc( (index-> M_max) * sizeof(HNSW_Node*));
    return;
}


float* _search_layer(
    HNSW_INDEX* index,float* arr, 
    int* entry_points,
    int num_closest,
    int layer){
    
    // initializing data sturcts
    Vector *visited = create_vector(sizeof(bool), index->ef_construction * 2);
    PriorityQueue* cand =  init_priority_queue(index->ef_construction * 2, true);
    PriorityQueue* result = init_priority_queue(index->ef_construction * 2, false);
    
    // pointer to array to save casting, I used generic vector
    HNSW_Node** nodes_array = (HNSW_Node**)index->nodes->items;


    for(int i =0; i < num_closest; i++){
        float dist = index->distance_function(nodes_array[entry_points[i]]->vector, arr, index->vector_dim);
        enqueue(cand, entry_points[i], dist);
        enqueue(result, entry_points[i], dist);
        insert_vector_element(visited, entry_points[i], true);
        bool visited_flag = true;
        insert_vector_element(visited, entry_points[i], &visited_flag);
    }

    while(cand->size > 0){
        PQNode* current_node = dequeue(cand);
        PQNode top_result = peek(result);

        if (current_node->distance > top_result.distance) {
            break; 
        }
        
        Neighbors* neighbors = nodes_array[current_node->id]->connections;
        
        for(int i =0; i < neighbors->connections->count; i++){
            int neighbor_id = ((int*)neighbors->connections->items)[i];
            
            bool* visited_arr = (bool*)visited->items;

            if (neighbor_id < visited->count && visited_arr[neighbor_id]){
                continue;
            }

            bool visited_flag = true;
            if (neighbor_id >= visited->count) {
                // Expand visited array if needed
                while (visited->count <= neighbor_id) {
                    bool false_flag = false;
                    append_vector_element(visited, &false_flag);
                }
            }
            set_vector_element(visited, neighbor_id, &visited_flag);
            float dist = index->distance_function(nodes_array[neighbor_id]->vector, arr, index->vector_dim);
            PQNode furthest_result = peek(result);
            if (dist < furthest_result.distance || result->size < index->ef_construction) {
                enqueue(cand, neighbor_id, dist);
                enqueue(result, neighbor_id, dist);
                
                // Remove worst element if over capacity
                if (result->size > index->ef_construction) {
                    dequeue(result);
                }
            }


        }
    }
    free_que(cand);
    free_vector(visited);
    return result;

}

    


int insert(HNSW_INDEX* index, float* arr){
    // Keeping this separate so we can have a unique id and add and remove nodes
    int node_id = index->max_node_id++;
    index->nodes->count++;
    // becuase i made this generic I have to cast
    HNSW_Node** nodes_array = (HNSW_Node**)index->nodes->items;

    // get level
    int level_assignment = __select_level_assignment(index);

    // make new node
    HNSW_Node* new_node = (HNSW_Node*)malloc(sizeof(HNSW_Node));
    ___create_node(new_node, node_id, arr, level_assignment, index);
    
    // adding node to graph 
    insert_vector_element(index->nodes, index->nodes->count - 1, &new_node);

    // first node in the graph
    if(index->graph_entry_point == -1){
        index->graph_entry_point = node_id;
        return node_id;
    }

    // Level one enter
    int* nearest = {index->graph_entry_point};
    int entry_level = nodes_array[nearest[0]]->max_layer;

    // greedy search





}

