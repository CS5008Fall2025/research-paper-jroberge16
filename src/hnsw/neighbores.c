
#include "neighbores.h"
#include "supporting_data_structures/vector.h"



Neighbors* neighbor_list_int(int capacity){
    Neighbors* neighbors = (Neighbors*)malloc(sizeof(Neighbors));
    neighbors->connections = create_vector(sizeof(int), capacity);
    return neighbors;
}

void free_neighbors(Neighbors* neighbors){
    if(neighbors == NULL) return;
    free_vector(neighbors->connections);
    free(neighbors);
}

void add_neighbor(Neighbors* neighbors, int connection ){
    append_vector_element(neighbors->connections, &connection);
}