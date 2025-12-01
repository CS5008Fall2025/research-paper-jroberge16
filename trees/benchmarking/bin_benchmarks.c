#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bin_benchmarks.h"
#include "../binnary/binnary.h"
#include "bench_utils.h"

#include "bin_benchmarks.h"
#include "../main.h"

typedef BENCH_OPERATION BIN_OPERATION;


static void __get_insertion_time(char* benchmark_file, char* benchmark_name, char* file_save_name, int total_tree_size, int n_skip);



/**
 * Run generic functions for AVL tree
 * @param tree AVL tre
 * @param value to be operated on
 * @param operation to perform
 * @param funcs ptrs to functions
 */
void run_bin_function(BINIndex* tree, int value, int operation){
    switch(operation){
        case INSERT_OP:
            insert_binary(tree, value);
            break;
        case SEARCH_OP:
            search_binary(tree, value);
            break;
        case DELETE_OP:
            delete_binary_value(tree, value);
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
}

void cleanup_bin_benchmark(char** results, int max_results, BINIndex* tree){
    free_results(results, max_results);
    free_binary_tree(tree);
}

/**
 * private function that run insertion benchmarks
 * @param benchmark_file file to read numbers from
 * @param benchmark_name name of the benchmark
 * @param file_save_name file to save results to
 * @param total_tree_size total size of the tree to grow to
 * @param n_skip number of insertions between timings
 */
static void __get_insertion_time(char* benchmark_file, char* benchmark_name, char* file_save_name, int total_tree_size, int n_skip){
    printf("⌚ Gathering Insertion Time\n");

    FILE *file;
    file = fopen(benchmark_file, "r");
    if (file == NULL) {
        perror("unable to open benchmark file");
        return;
    }
    // resutls get stored as an array of strings
    int max_results = (total_tree_size/n_skip) + 2;
    char **results = calloc(max_results, sizeof(char*));
    char buffer[LINE_BUFFER_SIZE];
    
    skip_header(file);
    assign_header("id,run_type,number_added,avg_time_per_insert,total_nodes,operation_count\n", results);

    BINIndex* tree = create_binary_tree();
    int result_index = 1;
    
    struct timespec batch_start, batch_end;
    int batch_count = 0;

    // I was getting to much noise with individual timmings
    // so i switched to batch timing. Although not perfect,
    // it should reduce noise between measurements
    for(int i = 1; i <= total_tree_size; i++){
        int num = get_next_number(file);
        if (num == -1) {
            printf("Last Line\n");
            break;
        }

        // Start timing at beginning of batch
        if (i % n_skip == 1) {
            clock_gettime(CLOCK_MONOTONIC, &batch_start);
            batch_count = 0;
        }
        // operation being timed
        insert_binary(tree, num);
        batch_count++;

        // End timing at end of batch
        if (i % n_skip == 0) {
            clock_gettime(CLOCK_MONOTONIC, &batch_end);
            
            double total_time = (batch_end.tv_sec - batch_start.tv_sec) + 
                               (batch_end.tv_nsec - batch_start.tv_nsec) / 1e9;
            double avg_time = total_time / batch_count;
            
            snprintf(buffer, sizeof(buffer), "%i,%s,%i,%.9f,%d,%lld\n", 
                    i, benchmark_name, num, avg_time, tree->total_Nodes, tree->total_operations);
            results[result_index++] = strdup(buffer);

            printf("\tProcessed %d with and avg of %.9f sec\n", i, avg_time);
        }
    }

    fclose(file);
    append_lines_to_file(results, file_save_name);
    cleanup_bin_benchmark(results, max_results, tree);
    printf("✅ Completed %d insertions\n", TOTAL_INSERTS);
}




/**
 * When given an operation type, runs the benchmark
 * program and get total elapsed time for `batch_size`
 * for an incrementally growing tree of size `total_tree_size`
 * which increments by `increment_tree_size` each iteration.
 * 
 * @param benchmark_file file to read numbers from
 * @param benchmark_name name of the benchmark
 * @param file_save_name file to save results to
 * @param total_tree_size total size of the tree to grow to
 * @param increment_tree_size size to increment tree by each iteration
 * @param batch_size number of operations to run per batch
 * @param operation_type type of operation to perform
 */
static void __get_regular_operation_time(
                                    char* benchmark_file,
                                    char* benchmark_name, 
                                    char* file_save_name,
                                    int total_tree_size,
                                    int increment_tree_size,
                                    int batch_size,
                                    BIN_OPERATION operation_type
                                    ){
    printf("⌚ Gathering %s Time\n", benchmark_name);

    FILE *file;
    file = fopen(benchmark_file, "r");
    if (file == NULL) {
        perror("unable to open benchmark file");
        return;
    }

    // results get stored as an array of strings
    int max_results = (total_tree_size/increment_tree_size) + 2;
    char **results = calloc(max_results, sizeof(char*));
    char buffer[LINE_BUFFER_SIZE];
    
    skip_header(file);
    assign_header("id,run_type,tree_size,batch_size,total_elapsed_time,ops_count\n", results);

    BINIndex* tree = create_binary_tree();
    int result_index = 1;
    int current_tree_size = 0;
    
    struct timespec batch_start, batch_end;

    // Order of operations: grow tree -> run batch of operations -> record time, end with write file
    for(int measurement = 0; measurement < total_tree_size/increment_tree_size; measurement++){
        // batch inserting by increment_tree_size
        for(int j = 0; j < increment_tree_size; j++){
            int num = get_next_number(file);
            if (num == -1) {
                printf("⚠️ Reached EOF at %d insertions\n", current_tree_size);
                goto end_benchmark;
            }
            insert_binary(tree, num);
            current_tree_size++;
        }

        int node_count = tree->total_Nodes;

        clock_gettime(CLOCK_MONOTONIC, &batch_start);

        // running batch_size operations
        for(int op = 0; op < batch_size; op++){
            int num = getRandomInRange(0, TOTAL_INSERTS - 1);
            run_bin_function(tree, num, operation_type);
        }
        clock_gettime(CLOCK_MONOTONIC, &batch_end);

        // When we deletes nodes we loose n thus our counts will be off
        // by a factor of n deletes. Adding them back in by sampling out
        // of distribution.
        int missing_nodes = node_count - tree->total_Nodes;
        if(missing_nodes >1){
            for(int r=0; r<missing_nodes;r++){
                // reinserting missing nodes
                int num = getRandomInRange(20000000, 40000000);
                insert_binary(tree, num);
                current_tree_size++;
            }
        }

        double total_time = (batch_end.tv_sec - batch_start.tv_sec) + 
                           (batch_end.tv_nsec - batch_start.tv_nsec) / 1e9;
        
        // Store result
        snprintf(buffer, sizeof(buffer), "%d,%s,%d,%d,%.10e,%lld\n", 
                 result_index, benchmark_name, tree->total_Nodes, batch_size, total_time, tree->total_operations);
        results[result_index++] = strdup(buffer);
        
        printf("\t%d operations on tree size %d: total=%.6f sec, avg=%.9f sec/op\n", 
               batch_size, tree->total_Nodes, total_time, total_time / batch_size);
    }

end_benchmark:
    fclose(file);
    append_lines_to_file(results, file_save_name);
    cleanup_bin_benchmark(results, max_results, tree);
    printf("✅ Completed benchmarking - final tree size: %d\n", current_tree_size);
}






/**
 * public function which runs the Binary benchmarking
 * @param args command line arguments
 */
void run_bin_benchmarks(CommandLineArgs args) {
    char filename[512];

    // Insertion Benchmarks
    snprintf(filename, sizeof(filename), "%sbin_inorder_results.csv", args.output_folder);
    __get_insertion_time("./data/samples/inorder_list.csv", "inorder_bin_insertion" ,filename, args.total_tree_size, args.increment_tree_size);
    snprintf(filename, sizeof(filename), "%sbin_random_results.csv", args.output_folder);
    __get_insertion_time("./data/samples/random_list.csv", "random_bin_insertion" ,filename, args.total_tree_size, args.increment_tree_size);
    
    //Search Benchmarks
    snprintf(filename, sizeof(filename), "%sbin_random_search_results.csv", args.output_folder);
    __get_regular_operation_time("./data/samples/random_list.csv", "random_bin_search", filename,
                                    args.total_tree_size, args.increment_tree_size, args.batch_size,SEARCH_OP);
    snprintf(filename, sizeof(filename), "%sbin_inorder_search_results.csv", args.output_folder);
    __get_regular_operation_time("./data/samples/inorder_list.csv", "inorder_bin_search", filename,
                                    args.total_tree_size, args.increment_tree_size, args.batch_size,SEARCH_OP);

    // Delete Benchmarks
    snprintf(filename, sizeof(filename), "%sbin_random_delete_results.csv", args.output_folder);
    __get_regular_operation_time("./data/samples/random_list.csv", "random_bin_delete", filename,
                                    args.total_tree_size, args.increment_tree_size, args.batch_size, DELETE_OP);
    snprintf(filename, sizeof(filename), "%sbin_inorder_delete_results.csv", args.output_folder);
    __get_regular_operation_time("./data/samples/inorder_list.csv", "inorder_bin_delete", filename,
                                    args.total_tree_size, args.increment_tree_size, args.batch_size, DELETE_OP);
}