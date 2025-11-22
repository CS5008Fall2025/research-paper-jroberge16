#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "avl.h"
// source: https://www.w3schools.com/python/python_dsa_avltrees.asp


// Declaring private methods
static AVLNode* __create_node(int value);
static AVLNode* __insert_avlTree(AVLNode* cur, int value, int* insert);
static int __get_max(int value1, int value2);
static AVLNode* __left_rotate(AVLNode* cur);
static AVLNode* __right_rotate(AVLNode* cur);
static AVLNode* __rebalance_tree(AVLNode* cur);
static AVLNode* get_min_node(AVLNode* node);
static AVLNode* __delete_avl_value(AVLNode *cur, int value, int* deleted);
static void __free_nodes(AVLNode* node);    

/**
 * creates index for a AVL tree
 * @return AVLIndex* pointer to created AVL tree index
 */
AVLIndex* create_avl_tree(){
    AVLIndex* index = (AVLIndex*)malloc(sizeof(AVLIndex));
    if(index==NULL){
        perror("Failed to allocate AVLIndex");
        exit(EXIT_FAILURE);
    }
    index->root = NULL;
    index->total_operations = 0;
    return index;
}

/**
 * creates a AVL Node
 * @param value value to be stored in node
 */
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


/**
 * insert value in to AVL tree (public)
 * @param index AVL tree index
 * @param value value to be inserted
 */
AVLIndex* insert_avl(AVLIndex* index, int value){
    AVLNode* root = index->root;
    
    // new tree
    if (root == NULL){
        AVLNode* new_node = __create_node(value);
        index->root = new_node;
        index->total_Nodes++;
        return index;
    } else {
        int insert = 0;
        index->root = __insert_avlTree(root, value, &insert);
        index->total_Nodes += insert;

    }
    return index;
} 

/**
 * retrun the max value when givne two intergers
 * 
 * @param value1 first integer
 * @param value2 second integer
 */
static int __get_max(int value1, int value2){
    return (value1 > value2) ? value1 : value2; 
}

/**
 * Calculates the Balance factor
 */
int get_avl_height(AVLNode* node){
    if(node==NULL){
        return 0;
    } else{
        return node->height;
    }
}

/**
 * Calculates the Balance factor
 * @param node current node to calculate balance for
 */
int get_balance(AVLNode* node){
    if(node==NULL){
        return 0;
    } else{
        return get_avl_height(node->left) - get_avl_height(node->right);
    }
}


// Rotations
/**
 * Performs a left rotation when given an AVL node:
 * @param cur current node to be rotated
*/
static AVLNode* __left_rotate(AVLNode* cur){
    AVLNode* cur_right = cur->right;
    AVLNode* cur_right_left = cur_right->left;

    cur_right->left  = cur;
    cur->right = cur_right_left;

    cur->height = 1 + __get_max(get_avl_height(cur->left), get_avl_height(cur->right));
    cur_right->height = 1 + __get_max(get_avl_height(cur_right->left), get_avl_height(cur_right->right));

    return cur_right;
}


/**
 * Performs a right rotation when given an AVL node:
 * @param cur current node to be rotated
*/
static AVLNode* __right_rotate(AVLNode* cur){

  AVLNode* cur_left =  cur->left;
  AVLNode* cur_left_right  = cur_left->right;

  cur_left->right = cur;
  cur->left = cur_left_right;
  cur->height = 1 + __get_max(get_avl_height(cur->left), get_avl_height(cur->right));
  cur_left->height = 1 + __get_max(get_avl_height(cur_left->left), get_avl_height(cur_left->right));
  return cur_left;
    
}


/**
 * Rebalances the AVL tree when given an AVL node:
 * @param cur current node to be rebalanced
*/
static AVLNode* __rebalance_tree(AVLNode* cur){
    cur->height = 1 + __get_max(get_avl_height(cur->left), get_avl_height(cur->right));

    // curr balance factors
    int cur_balance = get_balance(cur);

    // Left in Balance
    if(cur_balance > 1){

        int balance_left = get_balance(cur->left);

        //left left
        if (balance_left >= 0){
            return __right_rotate(cur);
        }

        //left right
        if (balance_left < 0){
            cur->left = __left_rotate(cur->left);
            return __right_rotate(cur);
        }
    }
    // RIGHT in balance
    else if (cur_balance < -1 ){
        int balance_right = get_balance(cur->right);
        
        //right right
        if (balance_right <= 0){
            return __left_rotate(cur);
        }

        // right left
        if (balance_right > 0){
            cur->right = __right_rotate(cur->right);
            return __left_rotate(cur);
        }
    }

    return cur;
}

/**
* Insert Value into AVL tree. This is not the main entry point see public version
* @param cur current node to perfrom recursion on
* @param value value to be inserted
*/
static AVLNode* __insert_avlTree(AVLNode* cur, int value, int* insert){
    if (cur == NULL){
        *insert = 1;
        return __create_node(value);
    }

    // insertion
    if (value <cur->value){
        cur->left = __insert_avlTree(cur->left, value, insert);
    } else if (value > cur->value){
        cur->right = __insert_avlTree(cur->right, value, insert);
    } else {
        // we skip duplicate values
        *insert = 0;
        return cur;
    }

    cur->height = 1 + __get_max(get_avl_height(cur->left), get_avl_height(cur->right));
    
    // Balancing logic
    cur = __rebalance_tree(cur);

    return cur;
}

static AVLNode* get_min_node(AVLNode* node){
    while (node->left != NULL)
        node = node->left;
    return node;
}

/**
 * Prviate method for deleintg a value from AVL tree
 * @param cur current node to perform recursion on
 * @param value value to be deleted
 * @param deleted pointer for tracking if node was deleted
 */
static AVLNode* __delete_avl_value(AVLNode *cur, int value, int* deleted){
    if(cur == NULL){
        *deleted = 0;
        return cur;
    }
    if(value < cur->value){
        cur->left = __delete_avl_value(cur->left, value, deleted);
    }
    else if(value > cur->value){
        cur->right = __delete_avl_value(cur->right, value, deleted);
    }
    // deleting node
    else{
        AVLNode* temp;
        
        if (cur->left == NULL){
            temp = cur->right;
            free(cur);
            *deleted = 1;
            return temp;
        }
        else if(cur->right == NULL){
            temp = cur->left;
            free(cur);
            *deleted = 1;
            return temp;
        }
        else{
            AVLNode* min_node = get_min_node(cur->right);
            cur->value = min_node->value;
            cur->right = __delete_avl_value(cur->right, min_node->value , deleted);
            *deleted = 1;

        }
    }
    cur = __rebalance_tree(cur);
    return cur;
}

AVLIndex* delete_avl_value(AVLIndex *index, int value){
    AVLNode* root = index->root;
    
    // new tree
    if (root == NULL){
        return index;
    } else {
        int deleted = 0;
        index->root = __delete_avl_value(root, value, &deleted);
        index->total_Nodes -= deleted;
    }
    return index;

}





/**
 * search AVL tree for a given value
 * @param index AVL tree index
 * @param value value to be searched
 */
AVLNode* search_avl(AVLIndex* index, int value){
    AVLNode* cur = index->root;
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
 

/**
 * post order traversal for freeing the nodes
 * 
 * @param node current node being freed
 */
static void __free_nodes(AVLNode* node) {
    if (node == NULL) {
        return;
    }
    // Traverse left
    __free_nodes(node->left);
    // traverse right
    __free_nodes(node->right);
    free(node);
}

void free_avl_tree(AVLIndex* index) {
    if (index == NULL) {
        return;
    }
    __free_nodes(index->root);
    free(index);
}
