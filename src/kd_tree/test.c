#include "../supporting_data_structures/priority_que.h"

// Replace the res_node linked list approach with priority queue
struct kdres {
    struct kdtree *tree;
    PriorityQueue *pq;  // Use your priority queue instead of linked list
    int k;              // For k-nearest searches
};

// Simplified nearest-k search using your priority queue
static void find_nearest_k(struct kdnode *node, const double *pos, 
                          PriorityQueue *max_heap, int k, int dim)
{
    if (!node) return;
    
    // Calculate distance to current node
    double dist_sq = 0;
    for (int i = 0; i < dim; i++) {
        dist_sq += SQ(node->pos[i] - pos[i]);
    }
    
    // Add to max-heap (keeps k closest points)
    if (max_heap->size < k) {
        enqueue(max_heap, (int)(intptr_t)node, dist_sq);
    } else if (dist_sq < peek(max_heap).distance) {
        dequeue(max_heap);  // Remove furthest
        enqueue(max_heap, (int)(intptr_t)node, dist_sq);
    }
    
    // Determine which subtree to search first
    double dx = pos[node->dir] - node->pos[node->dir];
    struct kdnode *near = (dx <= 0) ? node->left : node->right;
    struct kdnode *far = (dx <= 0) ? node->right : node->left;
    
    // Search near subtree
    find_nearest_k(near, pos, max_heap, k, dim);
    
    // Check if we need to search far subtree
    double max_dist = (max_heap->size < k) ? INFINITY : peek(max_heap).distance;
    if (SQ(dx) < max_dist) {
        find_nearest_k(far, pos, max_heap, k, dim);
    }
}

// Simplified k-nearest neighbor search
struct kdres *kd_nearest_k(struct kdtree *kd, const double *pos, int k)
{
    if (!kd || !kd->root) return NULL;
    
    struct kdres *rset = malloc(sizeof(*rset));
    if (!rset) return NULL;
    
    // Use max-heap (largest distance at top)
    rset->pq = init_priority_que(k + 1, false);  // min_heap=false for max-heap
    rset->tree = kd;
    rset->k = k;
    
    find_nearest_k(kd->root, pos, rset->pq, k, kd->dim);
    
    return rset;
}

// Simplified result iteration
void *kd_res_item(struct kdres *rset, double *pos)
{
    if (rset->pq->size == 0) return NULL;
    
    PQNode *node = dequeue(rset->pq);
    if (!node) return NULL;
    
    struct kdnode *kdn = (struct kdnode *)(intptr_t)node->id;
    
    if (pos) {
        memcpy(pos, kdn->pos, rset->tree->dim * sizeof(double));
    }
    
    void *data = kdn->data;
    free(node);
    return data;
}

// Simplified cleanup
void kd_res_free(struct kdres *rset)
{
    free_que(rset->pq);
    free(rset);
}