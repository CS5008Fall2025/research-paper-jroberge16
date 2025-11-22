#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "binnary.h"


// Declaring private methods
static BINNode* __create_node(int value);
static void __free_nodes(BINNode* node);
static void __insert_value(BINNode* node, int value);
static BINNode* __findMin(BINNode* curr);
static BINNode* __delete_binary_value(BINNode* curr, int value, int* deletion);
static void __free_nodes(BINNode* node);





/**
 * creates binary tree node
 * @param value value for node
 * @return node ptr
 */
static BINNode* __create_node(int value){
    BINNode *new_node = (BINNode*)malloc(sizeof(BINNode));
    if(new_node==NULL){
        perror("Failed to allocate BINNode");
        exit(EXIT_FAILURE);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = value;
    return new_node;
}


/**
 * creates binary tree
 * @return index of new tree
 */
BINIndex* create_binary_tree(){
    BINIndex* index = (BINIndex*)malloc(sizeof(BINIndex));
    if(index==NULL){
        perror("Failed to allocate BinIndex");
        exit(EXIT_FAILURE);
    }
    index->root = NULL;
    index->total_operations = 0;
    index->total_Nodes = 0;
    return index;
}


/**
 * private function for inserting a value in in a binnary tree
 * @param node current node
 * @param value value to be added
 */
static void __insert_value(BINNode* node, int value){

    while(node != NULL){
        // Traverse left or right
        if(value < node->value){
            if(node->left !=NULL){
                node = node->left;
            }else{
                node->left = __create_node(value);
                return;
            }
        } 
        // Right Traversal
        else if(value > node->value){
            if(node->right != NULL){
                node = node->right;
            }
            else{
                node->right = __create_node(value);
                return;
            }

        }else{
              /// we skip duplicates.
            return;
        }

    }
}

/**
 * Public method for insertion
 * @param bin tree
 * @param value to be added
 */
BINIndex* insert_binary(BINIndex* bin, int value){
    BINNode* root = bin->root;
    if (bin->root == NULL){
        bin->root  = __create_node(value);
        bin->total_Nodes += 1;
    } else{
        __insert_value(root, value);
        bin->total_Nodes += 1;
    }
    return bin;
}


/**
 * search Binary tree for a given value
 * @param index AVL tree index
 * @param value value to be searched
 */
BINNode* search_binary(BINIndex* index, int value){
    BINNode* cur = index->root;
    while(cur != NULL){
        if (cur->value == value){
            return cur;
        } else if (value < cur->value){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}


static BINNode* __findMin(BINNode* curr){
    while(curr!= NULL && curr->left!=NULL){
        curr = curr->left;
    }
    return curr;
}


static BINNode* __delete_binary_value(BINNode* curr, int value, int* deletion){
    // end of the line base case
    if(curr == NULL){
        return curr;
    }
    // traversal
    //left
    if (value < curr -> value){
        curr->left = __delete_binary_value(curr->left, value, deletion);
    }
    //right
    else if (value > curr -> value){
        curr->right = __delete_binary_value(curr->right, value, deletion);
    } 
    // we found the node
    else{
        // NULLs we drop without reconnecting
        if(curr->left == NULL){
            BINNode* temp = curr->right;
            free(curr);
            (*deletion)++;
            return temp;
        }

        else if(curr->right == NULL){
            BINNode* temp = curr->left;
            free(curr);
            (*deletion)++;
            return temp;
        }

        // have to pick the favorite (min) child
        BINNode* min  = __findMin(curr->right);
        curr->value = min->value;
        curr->right = __delete_binary_value(curr->right, min->value, deletion);
    }
    return curr;
}



BINIndex* delete_binary_value(BINIndex* index, int value){
    if(index == NULL){
        return index;
    }
    BINNode* root = index->root;
    int deletion = 0;

    if(root != NULL){
        root  = __delete_binary_value(root, value, &deletion);
        index->root = root;
        index->total_Nodes-= deletion;
        return index;
    }else{
        return index;
    }
}
static void __free_nodes(BINNode* node) {
    if (node == NULL) {
        return;
    }
    __free_nodes(node->left);
    __free_nodes(node->right);
    free(node);
}

void free_binary_tree(BINIndex* index) {
    if (index == NULL) {
        return;
    }
    __free_nodes(index->root);
    free(index);
}
