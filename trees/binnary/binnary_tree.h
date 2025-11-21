#ifndef BIN_H
#define BIN_H
// source https://www.geeksforgeeks.org/python/binary-tree-in-python/

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
    int total_operations;
};

BINIndex* create_tree();
BINIndex* insertBIN(BINIndex* index, int value);
BINIndex* delete_value(BINIndex *index, int value);
BINNode* searchBIN(BINIndex* index, int value);
int get_height(BINNode* node);
int get_balance(BINNode* node);
void print_tree(BINIndex* index);
void free_tree(BINIndex* index);

#endif