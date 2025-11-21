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
    int total_operations;
};

AVLIndex* create_tree();
AVLIndex* insertAVL(AVLIndex* index, int value);
AVLIndex* delete_value(AVLIndex *index, int value);
AVLNode* searchAVL(AVLIndex* index, int value);
int get_height(AVLNode* node);
int get_balance(AVLNode* node);
void print_tree(AVLIndex* index);
void free_tree(AVLIndex* index);


#endif