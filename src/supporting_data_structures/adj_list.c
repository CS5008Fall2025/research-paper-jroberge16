#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#include "adj_list.h"



adjNode* creat_adj_node(int v){
    struct adjNode* newNode = malloc(sizeof(adjNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* int_graph(int number_vertices, int is_directed){
    Graph* graph = malloc(sizeof(Graph));
    graph->number_of_vertices = number_vertices;
    graph->is_directed = is_directed;

    graph->adjList = malloc(number_vertices * sizeof(adjNode*));

    for(int i = 0; i < number_vertices; i++){
        graph->adjList[i] = NULL;
    }

    return graph;
}

void add_edge(Graph* graph, int src, int dest){
    adjNode* newNode = creat_adj_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if(!graph->is_directed){
        newNode = creat_adj_node(src);
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    }
}
