// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <string.h>

// #include "../avl/avl.h"


// void test_avl() {
//     AVLIndex* tree = create_avl_tree();
//     assert(tree != NULL);
//     assert(tree->root == NULL);
//     printf("\t✅ AVL Tree Initialization\n");

//     // left roation => pivot on 2
//     tree = insert_avl(tree, 1);
//     tree = insert_avl(tree, 2);
//     tree = insert_avl(tree, 3);
//     assert(tree->root->value == 2);
//     assert(tree->root->left->value == 1);
//     assert(tree->root->right->value == 3);
//     printf("\t✅ Left Rotation\n");
//     free_avl_tree(tree);

//     //right rotation => pivot on 2
//     tree = create_avl_tree();
//     tree = insert_avl(tree, 3);
//     tree = insert_avl(tree, 2);
//     tree = insert_avl(tree, 1);

//     assert(tree->root->value == 2);
//     assert(tree->root->left->value == 1);
//     assert(tree->root->right->value == 3);
//     free_avl_tree(tree);
//     printf("\t✅ Right Rotation\n");

//     //left- right Rotation => pivot on 2
//     tree = create_avl_tree();
//     tree = insert_avl(tree, 1);
//     tree = insert_avl(tree, 3);
//     tree = insert_avl(tree, 2);
//     assert(tree->root->value == 2);
//     assert(tree->root->left->value == 1);
//     assert(tree->root->right->value == 3);
//     printf("\t✅ Left Right Rotation\n");

    
//     //right - left Rotation => pivot on 2
//     tree = create_avl_tree();
//     tree = insert_avl(tree, 3);
//     tree = insert_avl(tree, 1);
//     tree = insert_avl(tree, 2);
//     assert(tree->root->value == 2);
//     assert(tree->root->left->value == 1);
//     assert(tree->root->right->value == 3);
//     printf("\t✅ Left Right Rotation\n");


//     //test delete
//     tree = create_avl_tree();
//     tree = insert_avl(tree, 20);
//     tree = insert_avl(tree, 10);
//     tree = insert_avl(tree, 30);
//     tree = insert_avl(tree, 5);
//     tree = insert_avl(tree, 15);
//     tree = insert_avl(tree, 25);
//     tree = insert_avl(tree, 35);
//     // root node should be replace by 25
//     tree = delete_avl_value(tree, 20);
//     assert(tree->root->value == 25);
//     printf("\t✅ Root Deletion\n");

//     // leaf node deletion
//     tree = delete_avl_value(tree, 35);
//     assert(tree->root->right->right == NULL);
//     printf("\t✅ Leaf Deletion\n");


//     // find AVL
//     AVLNode* node = search_avl(tree, 5);
//     assert(node->value == 5);
//     printf("\t✅ find value passed\n");
//     free_avl_tree(tree);
    

// }

// int main() {
//     test_avl();
//     printf("🥳 All tests passed!\n");
//     return 0;
// }



#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "trees/avl/avl.h"

// Helper function to verify AVL property
int verify_avl_property(AVLNode* node) {
    if (node == NULL) return 1;
    
    int balance = get_balance(node);
    if (balance > 1 || balance < -1) {
        printf("❌ Balance violation at node %d: balance = %d\n", node->value, balance);
        return 0;
    }
    
    return verify_avl_property(node->left) && verify_avl_property(node->right);
}

// Helper function to count nodes
int count_nodes(AVLNode* node) {
    if (node == NULL) return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// Helper function to verify BST property
int verify_bst_property(AVLNode* node, int min, int max) {
    if (node == NULL) return 1;
    
    if (node->value <= min || node->value >= max) {
        printf("❌ BST violation at node %d (min=%d, max=%d)\n", node->value, min, max);
        return 0;
    }
    
    return verify_bst_property(node->left, min, node->value) && 
           verify_bst_property(node->right, node->value, max);
}

void test_basic_insertion() {
    printf("\n=== Test Basic Insertion ===\n");
    
    AVLIndex* tree = create_avl_tree();
    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->total_Nodes == 0);
    
    // Insert single element
    tree = insert_avl(tree, 10);
    assert(tree->root != NULL);
    assert(tree->root->value == 10);
    assert(tree->total_Nodes == 1);
    
    printf("✅ Basic insertion works\n");
    free_avl_tree(tree);
}

void test_left_rotation() {
    printf("\n=== Test Left Rotation ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    // Insert in ascending order: 1, 2, 3
    // Should trigger left rotation at root
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 2);
    tree = insert_avl(tree, 3);
    
    // After rotation, root should be 2
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    assert(tree->total_Nodes == 3);
    assert(verify_avl_property(tree->root));
    
    printf("✅ Left rotation works\n");
    free_avl_tree(tree);
}

void test_right_rotation() {
    printf("\n=== Test Right Rotation ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    // Insert in descending order: 3, 2, 1
    // Should trigger right rotation at root
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 2);
    tree = insert_avl(tree, 1);
    
    // After rotation, root should be 2
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    assert(tree->total_Nodes == 3);
    assert(verify_avl_property(tree->root));
    
    printf("✅ Right rotation works\n");
    free_avl_tree(tree);
}

void test_left_right_rotation() {
    printf("\n=== Test Left-Right Rotation ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    // Insert: 3, 1, 2
    // Should trigger left-right rotation
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 2);
    
    // After rotation, root should be 2
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    assert(verify_avl_property(tree->root));
    
    printf("✅ Left-Right rotation works\n");
    free_avl_tree(tree);
}

void test_right_left_rotation() {
    printf("\n=== Test Right-Left Rotation ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    // Insert: 1, 3, 2
    // Should trigger right-left rotation
    tree = insert_avl(tree, 1);
    tree = insert_avl(tree, 3);
    tree = insert_avl(tree, 2);
    
    // After rotation, root should be 2
    assert(tree->root->value == 2);
    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 3);
    assert(verify_avl_property(tree->root));
    
    printf("✅ Right-Left rotation works\n");
    free_avl_tree(tree);
}

void test_duplicate_insertion() {
    printf("\n=== Test Duplicate Insertion ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    tree = insert_avl(tree, 5);
    tree = insert_avl(tree, 5);  // Duplicate
    tree = insert_avl(tree, 5);  // Duplicate
    
    assert(tree->total_Nodes == 1);  // Should only have 1 node
    
    printf("✅ Duplicate rejection works\n");
    free_avl_tree(tree);
}

void test_sequential_insertions() {
    printf("\n=== Test Sequential Insertions (Worst Case) ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    int n = 1000;
    for (int i = 0; i < n; i++) {
        tree = insert_avl(tree, i);
    }
    
    assert(tree->total_Nodes == n);
    assert(verify_avl_property(tree->root));
    assert(verify_bst_property(tree->root, -1, n));
    
    // Check tree height is logarithmic
    int height = get_avl_height(tree->root);
    int max_height = (int)(1.44 * (height + 2));  // AVL max height ≈ 1.44 log(n)
    printf("Tree height: %d (n=%d)\n", height, n);
    assert(height <= 20);  // log2(1000) ≈ 10, AVL allows ~1.44x
    
    printf("✅ Sequential insertions maintain AVL property\n");
    free_avl_tree(tree);
}

void test_random_insertions() {
    printf("\n=== Test Random Insertions ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    int values[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35, 55, 65, 77, 85};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        tree = insert_avl(tree, values[i]);
    }
    
    assert(tree->total_Nodes == n);
    assert(verify_avl_property(tree->root));
    assert(verify_bst_property(tree->root, 0, 100));
    
    printf("✅ Random insertions maintain AVL property\n");
    free_avl_tree(tree);
}

void test_search() {
    printf("\n=== Test Search ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    int values[] = {50, 25, 75, 10, 30, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        tree = insert_avl(tree, values[i]);
    }
    
    // Search for existing values
    for (int i = 0; i < n; i++) {
        AVLNode* found = search_avl(tree, values[i]);
        assert(found != NULL);
        assert(found->value == values[i]);
    }
    
    // Search for non-existing values
    assert(search_avl(tree, 100) == NULL);
    assert(search_avl(tree, -5) == NULL);
    assert(search_avl(tree, 55) == NULL);
    
    printf("✅ Search works correctly\n");
    free_avl_tree(tree);
}

void test_large_dataset() {
    printf("\n=== Test Large Dataset (10,000 insertions) ===\n");
    
    AVLIndex* tree = create_avl_tree();
    
    int n = 10000;
    for (int i = 0; i < n; i++) {
        tree = insert_avl(tree, i);
        
        // Verify every 1000 insertions
        if ((i + 1) % 1000 == 0) {
            assert(verify_avl_property(tree->root));
            printf("  Verified at %d insertions\n", i + 1);
        }
    }
    
    assert(tree->total_Nodes == n);
    assert(verify_avl_property(tree->root));
    
    int height = get_avl_height(tree->root);
    printf("Final tree height: %d (expected ~14-20 for 10,000 nodes)\n", height);
    
    printf("✅ Large dataset maintains AVL property\n");
    free_avl_tree(tree);
}

int main() {
    printf("╔═══════════════════════════════════╗\n");
    printf("║   AVL Tree Correctness Tests     ║\n");
    printf("╚═══════════════════════════════════╝\n");
    
    test_basic_insertion();
    test_left_rotation();
    test_right_rotation();
    test_left_right_rotation();
    test_right_left_rotation();
    test_duplicate_insertion();
    test_sequential_insertions();
    test_random_insertions();
    test_search();
    test_large_dataset();
    
    printf("\n╔═══════════════════════════════════╗\n");
    printf("║   ✅ ALL TESTS PASSED!            ║\n");
    printf("╚═══════════════════════════════════╝\n");
    
    return 0;
}