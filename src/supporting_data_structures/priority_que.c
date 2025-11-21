#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "priority_que.h"

// source: https://www.geeksforgeeks.org/c/c-program-to-implement-priority-queue/

PriorityQueue* init_priority_que(int capacity, bool min_heap){
    PriorityQueue* new_que = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    new_que->nodes  = (PQNode*)malloc(sizeof(PQNode)*capacity);
    new_que->size = 0;
    new_que->capacity = capacity;
    new_que->min_heap = min_heap;
    return new_que;
}


bool __compare(PriorityQueue *pq, float node1, float node2) {
    if(pq->min_heap){
        return (node1 < node2);
    }else{
        return (node1 > node2);
    }
}

void __swap_pq(PQNode *node1, PQNode *node2){
    PQNode temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void heapifyUp(PriorityQueue* pq, int index)
{
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    if (__compare(pq, pq->nodes[index].distance, pq->nodes[parent].distance)) {
        __swap_pq(&pq->nodes[parent], &pq->nodes[index]);
        heapifyUp(pq, parent);
    }
}

void heapifyDown(PriorityQueue* pq, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size &&  __compare(pq, pq->nodes[left].distance, pq->nodes[smallest].distance))
        smallest = left;

    if (right < pq->size && __compare(pq, pq->nodes[right].distance, pq->nodes[smallest].distance))
        smallest = right;

    if (smallest != index) {
        __swap_pq(&pq->nodes[index], &pq->nodes[smallest]);
        heapifyDown(pq, smallest);
    }
}

PQNode* dequeue(PriorityQueue* pq)
{
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return NULL;
    }
    //get node
    PQNode* node = (PQNode*)malloc(sizeof(PQNode));
    *node = pq->nodes[0];

    pq->nodes[0] = pq->nodes[--pq->size];
    heapifyDown(pq, 0);
    return node;
}

void enqueue(PriorityQueue* pq, int id, float distance)
{
    if (pq->size >= (int)(pq->capacity*.75)) {
        pq->capacity *= 2;
        pq->nodes = (PQNode*)realloc(pq->nodes, pq->capacity * sizeof(PQNode));
        if (!pq->nodes) {
            perror("Failed to reallocate priority queue nodes");
            exit(EXIT_FAILURE);
        } 
    }

    pq->nodes[pq->size].id = id;
    pq->nodes[pq->size].distance = distance;
    pq->size++;
    heapifyUp(pq, pq->size);
}


PQNode peek(PriorityQueue* pq)
{
    return pq->nodes[0];
}



void free_que(PriorityQueue *que){
    free(que->nodes);
    free(que);
}


