#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../trees/binnary/binnary.h"



void test_binary() {
    BINIndex* tree = create_binary_tree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    printf("\t✅ Binary Tree Initialization\n");

    // left rotation => pivot on 2
    tree = insert_binary(tree, 2);
    tree = insert_binary(tree, 1);
    tree = insert_binary(tree, 3);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Insertion\n");
    
    // find AVL
    BINNode* node = search_binary(tree, 3);
    assert(node->value == 3);
    printf("\t✅ find value passed\n");

    // leaf node deletion
    tree = delete_binary_value(tree, 3);
    node = search_binary(tree, 3);
    assert(node == NULL);
    printf("\t✅ node removed\n");


}

int main() {
    test_binary();
    printf("🥳 All tests passed!\n");
    return 0;
}