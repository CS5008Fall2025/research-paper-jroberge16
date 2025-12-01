#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "benchmarking/avl_benchmarks.h"
#include "benchmarking/bin_benchmarks.h"
#include "main.h"








CommandLineArgs processCommandLineArgs(int argc, char** argv){
    CommandLineArgs args;

    if (argc == 1) {
        // Defaults
        // Max values for an AVL
        args.total_tree_size = 25000000;
        args.increment_tree_size = 50000;
        args.batch_size = 5000;

        strncpy(args.output_folder, "./data/results/", sizeof(args.output_folder) - 1);
        args.output_folder[sizeof(args.output_folder) - 1] = '\0';
        
        strncpy(args.dataStructure, "avl", sizeof(args.dataStructure) - 1);
        args.dataStructure[sizeof(args.dataStructure) - 1] = '\0';
    }
    else if (argc == 5) {
        // check alg
        if (strcmp(argv[1], "avl") != 0 && strcmp(argv[1], "bin") != 0) {
            printf("Error: Not a valid data structure. Use 'avl' or 'bin'\n not %s", argv[1]);
            exit(1);
        }

        strncpy(args.dataStructure, argv[1], sizeof(args.dataStructure) - 1);
        args.dataStructure[sizeof(args.dataStructure) - 1] = '\0';
        args.total_tree_size = atoi(argv[2]);
        args.increment_tree_size = atoi(argv[3]);
        args.batch_size = atoi(argv[4]);

        // Defualt output folder
        strncpy(args.output_folder, "./data/results/", sizeof(args.output_folder) - 1);
        args.output_folder[sizeof(args.output_folder) - 1] = '\0';
    } else{
        printf("Error: Invalid number of arguments.\n");
        printf("Args should be <data_structure> <total_tree_size> <increment_tree_size> <batch_size>\n");
        exit(1);
    }

    return args;
}

int main(int argc, char** argv){
    printf("Running Benchmarks for Trees\n");
    CommandLineArgs args = processCommandLineArgs(argc, argv);
    if (strcmp(args.dataStructure, "avl") == 0){
        run_avl_benchmarks(args);
    } else if (strcmp(args.dataStructure, "bin") == 0) {
        run_bin_benchmarks(args);
    } else {
        
    }
    return 0;
}