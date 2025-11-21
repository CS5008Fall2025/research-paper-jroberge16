#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../avl/avl.h"


void test_avl() {
    AVLIndex* tree = create_tree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    printf("\t✅ AVL Tree Initialization\n");

    // left roation => pivot on 2
    tree = insertAVL(tree, 1);
    tree = insertAVL(tree, 2);
    tree = insertAVL(tree, 3);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Rotation\n");
    free_tree(tree);

    //right rotation => pivot on 2
    tree = create_tree();
    tree = insertAVL(tree, 3);
    tree = insertAVL(tree, 2);
    tree = insertAVL(tree, 1);

    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    free_tree(tree);
    printf("\t✅ Right Rotation\n");

    //left- right Rotation => pivot on 2
    tree = create_tree();
    tree = insertAVL(tree, 1);
    tree = insertAVL(tree, 3);
    tree = insertAVL(tree, 2);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Right Rotation\n");

    
    //right - left Rotation => pivot on 2
    tree = create_tree();
    tree = insertAVL(tree, 3);
    tree = insertAVL(tree, 1);
    tree = insertAVL(tree, 2);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Right Rotation\n");


    //test delete
    tree = create_tree();
    tree = insertAVL(tree, 20);
    tree = insertAVL(tree, 10);
    tree = insertAVL(tree, 30);
    tree = insertAVL(tree, 5);
    tree = insertAVL(tree, 15);
    tree = insertAVL(tree, 25);
    tree = insertAVL(tree, 35);
    // root node should be replace by 25
    tree = delete_value(tree, 20);
    printf("\t✅ Root Deletion\n");

    // leaf node deletion
    tree = delete_value(tree, 35);
    assert(tree->root->right->right == NULL);
    printf("\t✅ Leaf Deletion\n");

}

int main() {
    test_avl();
    printf("🥳 All tests passed!\n");
    return 0;
}