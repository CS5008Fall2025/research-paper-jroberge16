#include <stdlib.h>
#include <stdint.h>
// source: https://www.geeksforgeeks.org/c/c-program-to-implement-adjacency-list/


typedef struct adjNode {
    int vertex;
    struct adjNode* next;
} adjNode;

typedef struct Graph{
    int number_of_vertices;
    adjNode** adjList;
    int is_directed;
} Graph;


adjNode* creat_adj_node(int v);
Graph* int_graph(int number_vertices, int is_directed);
void add_edge(Graph* graph, int src, int dest);