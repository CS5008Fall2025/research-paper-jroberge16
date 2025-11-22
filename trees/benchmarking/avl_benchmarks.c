#include "avl_benchmarks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../avl/avl.h"
#include "bench_utils.h"


static void __get_insertion_time(char* benchmark_file, char* benchmark_name, char* file_save_name);




static void __get_insertion_time(char* benchmark_file, char* benchmark_name, char* file_save_name){
    printf("⌚ Gathering Insertion Time\n");
    //Getting file
    FILE *file;
    file = fopen(benchmark_file, "r");
    if (file == NULL) {
        perror("FAILED to OPEN FILE");
        return;
    }

    // Skip header row
    char header[LINE_BUFFER_SIZE];
    fgets(header, LINE_BUFFER_SIZE, file);

    // running benchmarks
    char **results = malloc((TOTAL_INSERTS+2) * sizeof(char*));
    char buffer[250];

    snprintf(buffer, sizeof(buffer), "id,run_type,number_added,time_taken,operations\n");
    results[0] = strdup(buffer);
    
    AVLIndex* tree = create_avl_tree();
    clock_t start = clock();
    
    for(int i = 1; i <= TOTAL_INSERTS; i++){
        int num = get_next_number(file);
        if (num == -1) {
            printf("Warning: Reached end of file at iteration %d\n", i);
            break;
        }
        
        insert_avl(tree, num);
        clock_t current = clock();
        double time_taken = (double)(current - start) / CLOCKS_PER_SEC;

        snprintf(buffer, sizeof(buffer), "%i,%s,%i,%f,%i", i, benchmark_name, num, time_taken, tree->total_operations);
        results[i] = strdup(buffer);
        
        // Progress indicator every 1000 inserts
        if (i % 1000 == 0) {
            printf("  Processed %d/%d insertions (%.1f%%)\n", i, TOTAL_INSERTS, (i * 100.0) / TOTAL_INSERTS);
        }
    }
    results[TOTAL_INSERTS + 1] = NULL;
    printf("✅ Completed %d insertions\n", TOTAL_INSERTS);

    fclose(file);
    append_lines_to_file(results, file_save_name);
    
    for(int i = 0; i <= TOTAL_INSERTS; i++){
        free(results[i]);
    }
    free(results);
    free_avl_tree(tree);
}





void run_avl_benchmarks() {

    __get_insertion_time("./data/random_list.csv", "biased_avl_insertion" ,"./data/avl_biased_results.csv");
    
}