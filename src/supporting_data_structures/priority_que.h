#ifndef PRIORITY_QUE_H
#define PRIORITY_QUE_H

#include <stdbool.h>
#include <stdlib.h>



typedef struct PQNode {
    int id;
    float distance;
} PQNode;

typedef struct PriorityQueue {
    PQNode *nodes;
    int size;
    int capacity;
    bool min_heap;
} PriorityQueue;

PriorityQueue* init_priority_que(int capacity, bool min_heap);
bool __compare(PriorityQueue *pq, float node1, float node2);
void __swap_pq(PQNode *node1, PQNode *node2);
void heapifyUp(PriorityQueue* pq, int index);
void heapifyDown(PriorityQueue* pq, int index);
PQNode* dequeue(PriorityQueue* pq);
void enqueue(PriorityQueue* pq, int id, float distance);
PQNode peek(PriorityQueue* pq);
void free_que(PriorityQueue *que);

#endif