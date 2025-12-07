#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../trees/avl/avl.h"


void test_avl() {
    AVLIndex* tree = create_avl_tree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    printf("\t✅ AVL Tree Initialization\n");

    // left roation => pivot on 2
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 2);
    tree = insert_avl(tree, 3);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Rotation\n");
    free_avl_tree(tree);

    //right rotation => pivot on 2
    tree = create_avl_tree();
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 2);
    tree = insert_avl(tree, 1);

    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    free_avl_tree(tree);
    printf("\t✅ Right Rotation\n");

    //left- right Rotation => pivot on 2
    tree = create_avl_tree();
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 2);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Right Rotation\n");

    
    //right - left Rotation => pivot on 2
    tree = create_avl_tree();
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 2);
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    printf("\t✅ Left Right Rotation\n");


    //test delete
    tree = create_avl_tree();
    tree = insert_avl(tree, 20);
    tree = insert_avl(tree, 10);
    tree = insert_avl(tree, 30);
    tree = insert_avl(tree, 5);
    tree = insert_avl(tree, 15);
    tree = insert_avl(tree, 25);
    tree = insert_avl(tree, 35);
    // root node should be replace by 25
    tree = delete_avl_value(tree, 20);
    assert(tree->root->value == 25);
    printf("\t✅ Root Deletion\n");

    // leaf node deletion
    tree = delete_avl_value(tree, 35);
    assert(tree->root->right->right == NULL);
    printf("\t✅ Leaf Deletion\n");


    // find AVL
    AVLNode* node = search_avl(tree, 5);
    assert(node->value == 5);
    printf("\t✅ find value passed\n");
    free_avl_tree(tree);
    

}

int main() {
    test_avl();
    printf("🥳 All tests passed!\n");
    return 0;
}

