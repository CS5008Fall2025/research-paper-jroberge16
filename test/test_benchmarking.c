#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "../trees/benchmarking/avl_benchmarks.h"
#include "../trees/benchmarking/bin_benchmarks.h"


int isFiles(const char *file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        return 1;
    } else {
        fclose(fptr);
        return 0;
    }
}


int count_file_lines(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("issue with file opening");
        return -1;
    }

    int count = 0;
    char buffer[LINE_BUFFER_SIZE];
    while (fgets(buffer, LINE_BUFFER_SIZE, file) != NULL) {
        count++;
    }

    fclose(file);
    return count;
}

void test_benchmarking() {

    CommandLineArgs args;
    args.total_tree_size = 50;
    args.increment_tree_size = 10;
    args.batch_size = 5;

    // Adding to test directory
    strncpy(args.output_folder, "./test/test_results/", sizeof(args.output_folder) - 1);
    args.output_folder[sizeof(args.output_folder) - 1] = '\0';



    // clean up folders
    rmdir(args.output_folder);
    mkdir(args.output_folder, 0755); 

    //******************* AVL Benchmarking *******************
    run_avl_benchmarks(args);

    // Check for Files Existence
    assert(isFiles("./test/test_results/avl_inorder_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_inorder_results.csv") ==  6);
    printf("\t✅ AVL Insert in order Benchmark\n");


    assert(isFiles("./test/test_results/avl_random_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_random_results.csv") == 6);
    printf("\t✅ AVL Insert Random Benchmark\n");


    assert(isFiles("./test/test_results/avl_random_search_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_random_search_results.csv") == 6);
    printf("\t✅ AVL Search Random Benchmark\n");


    assert(isFiles("./test/test_results/avl_inorder_search_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_inorder_search_results.csv") == 6);
    printf("\t✅ AVL Search in order Benchmark\n");


    assert(isFiles("./test/test_results/avl_random_delete_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_random_delete_results.csv") == 6);
    printf("\t✅ AVL Delete Random Benchmark\n");

    assert(isFiles("./test/test_results/avl_inorder_delete_results.csv") == 0);
    assert(count_file_lines("./test/test_results/avl_inorder_delete_results.csv") == 6);
    printf("\t✅ AVL Delete in order Benchmark\n");

    //******************* BIN Benchmarking *******************
    run_bin_benchmarks(args);
    // Check for Files Existence
    
    assert(isFiles("./test/test_results/bin_inorder_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_inorder_results.csv") == 6);
    printf("\t✅ BIN Insert in order Benchmark\n");
    
    assert(isFiles("./test/test_results/bin_random_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_random_results.csv") == 6);
    printf("\t✅ BIN Insert Random Benchmark\n");
    
    assert(isFiles("./test/test_results/bin_random_search_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_random_search_results.csv") == 6);
    printf("\t✅ BIN Search Random Benchmark\n");
    
    assert(isFiles("./test/test_results/bin_inorder_search_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_inorder_search_results.csv") == 6);
    printf("\t✅ BIN Search in order Benchmark\n");
    
    assert(isFiles("./test/test_results/bin_random_delete_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_random_delete_results.csv") == 6);
    printf("\t✅ BIN Delete Random Benchmark\n");
    
    assert(isFiles("./test/test_results/bin_inorder_delete_results.csv") == 0);
    assert(count_file_lines("./test/test_results/bin_inorder_delete_results.csv") == 6);
    printf("\t✅ BIN Delete in order Benchmark\n");

    // clean up folders
    rmdir(args.output_folder);
    mkdir(args.output_folder, 0755); 
}

int main(int argc, char** argv) {
    test_benchmarking();
    printf("🥳 All tests passed!\n");
    return 0;
}

