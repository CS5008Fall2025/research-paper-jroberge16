#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "adj_list.h"




void test_adj_list() {
    Graph* graph = int_graph(5, 0);
    assert(graph != NULL);
    assert(graph->number_of_vertices == 5);
    assert(graph->is_directed == 0);
    printf("\t✅ Adjacency List Initialization\n");

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 2);
    add_edge(graph, 3, 4);

    adjNode* adj = graph->adjList[1];
    int count = 0;
    while (adj != NULL) {
        count++;
        adj = adj->next;
    }
    assert(count == 4);
    printf("\t✅ add_edge and adjacency verification\n");
}

int main() {
    test_adj_list();
    printf("🥳 All tests passed!\n");
    return 0;
}