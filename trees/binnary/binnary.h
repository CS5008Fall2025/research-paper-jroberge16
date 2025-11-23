#ifndef BIN_H
#define BIN_H
// source https://www.geeksforgeeks.org/python/binary-tree-in-python/
//source https://www.geeksforgeeks.org/dsa/deletion-in-binary-search-tree/

typedef struct BINNode BINNode;
typedef struct BINIndex BINIndex;

struct BINNode {
    int value;
    BINNode* left;
    BINNode* right;
};

struct BINIndex {
    BINNode* root;
    int total_Nodes;
    long long total_operations;
};

BINIndex* create_binary_tree();
BINIndex* insert_binary(BINIndex* index, int value);
BINIndex* delete_binary_value(BINIndex *index, int value);
BINNode* search_binary(BINIndex* index, int value);
int get_height(BINNode* node);
int get_balance(BINNode* node);
void print_tree(BINIndex* index);
void free_tree(BINIndex* index);
void free_binary_tree(BINIndex* index);


#endif