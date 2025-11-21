#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "binnary_tree.h"


// Declaring private methods
static BINNode* __create_node(int value);
static void __free_nodes(BINNode* node);



BINIndex* create_binnary_tree(){
    BINIndex* index = (BINIndex*)malloc(sizeof(BINIndex));
    if(index==NULL){
        perror("Failed to allocate BINIndex");
        exit(EXIT_FAILURE);
    }
    index->root = NULL;
    index->total_operations = 0;
    return index;
}


static BINNode* __create_node(int value){
    BINNode *new_node = (BINNode*)malloc(sizeof(BINNode));
    if(new_node==NULL){
        perror("Failed to allocate AVLIndex");
        exit(EXIT_FAILURE);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static AVLNode* __create_node(int value){
    AVLNode *new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if(new_node==NULL){
        perror("Failed to allocate AVLIndex");
        exit(EXIT_FAILURE);
    }
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = value;
    return new_node;
}
