
// single node in the KD Tree
typedef struct KDNode{
    int id;
    float *point;
    struct KDNode *left;
    struct KDNode *right;
    int axis;
} KDNode;

// Houses entire index
typedef struct KDIndex {
    KDNode *root;
    int vector_dim;
    int size;
    float (*distance_function)(const float*, const float*, int);
} KDIndex;

// SINGLE KD-Tree result
typedef struct KDResult{
    int id;
    float distance;
} KDResult;

// Multiple KD-Tree results
typedef struct MKDResult{
    KDResult* results;
    int count;
} MKDResult;



int




