#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "priority_que.h"


void test_priority_queue() {
    PriorityQueue* pq = init_priority_que(5, true);
    assert(pq != NULL);
    assert(pq->capacity == 5);
    assert(pq->size == 0);
    assert(pq->min_heap == true);
    printf("\t✅ Priority Queue initialized\n");

    enqueue(pq, 1, 10.0);
    enqueue(pq, 2, 5.0);
    enqueue(pq, 3, 7.5);
    printf("\t✅ Priority Queue enqueue\n");
    PQNode peeked = peek(pq);
    assert(peeked.id == 2 && peeked.distance == 5.0);
    printf("\t✅ Priority Queue peek\n");

    PQNode* dequeued = dequeue(pq);
    assert(dequeued->id == 2 && dequeued->distance == 5.0);
    assert(pq->size == 2);
    printf("\t✅ Priority Queue dequeue\n");
    free(dequeued);
    free_que(pq);
    printf("\t✅ Priority Queue free\n");
}


int main() {
    printf("🧪 Testing Min Heap Implementation\n");
    test_priority_queue();
    printf("🥳 ALL TESTS PASSED\n");
    return 0;
}