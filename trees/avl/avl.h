#ifndef AVL_H
#define AVL_H

typedef struct AVLNode AVLNode;
typedef struct AVLIndex AVLIndex;

struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
};

struct AVLIndex {
    AVLNode* root;
    int total_Nodes;
    long long int total_operations;
    long int rotations;
};

AVLIndex* create_avl_tree();
AVLIndex* insert_avl(AVLIndex* index, int value);
AVLIndex* delete_avl_value(AVLIndex *index, int value);
AVLNode* search_avl(AVLIndex* index, int value);
int get_avl_height(AVLNode* node);
int get_balance(AVLNode* node);
void free_avl_tree(AVLIndex* index);


#endif