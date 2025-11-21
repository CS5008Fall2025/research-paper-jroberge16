#ifndef NEIGHBORES_H
#define NEIGHBORES_H

#include "supporting_data_structures/vector.h"

typedef struct Neighbors {
    Vector *connections;
} Neighbors;

Neighbors* neighbor_list_int(int capacity);
void free_neighbors(Neighbors* neighbors);
void add_neighbor(Neighbors* neighbors, int connection);

#endif