#include <stdio.h>
#include <stdlib.h>
#include "bench_utils.h"
#include "avl_benchmarks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../avl/avl.h"


typedef void (*AVL_OP_FUNC)(AVLIndex* tree, int value);

/**
 * Retrieves the next number in a file
 * @param file file pointer
 * @return next integer from file, or -1 if EOF
 */
int get_next_number(FILE* file){
    char buffer[LINE_BUFFER_SIZE];
    if(fgets(buffer, LINE_BUFFER_SIZE, file) != NULL){
        int number = atoi(buffer);
        return number;
    } else{
        return -1;
    }
}


/**
 * Appends to a CSV file
 * @param lines array of strings to write
 * @param file_name name of the file to write to
 */
void append_lines_to_file(char** lines, char* file_name){
        FILE* fptr = fopen(file_name, "w");
        if(fptr == NULL){
            perror("Failed to open file for writing");
            return;
        }
        for(int i =0; lines[i] != NULL; i++){
            fputs(lines[i], fptr);
        }
        fclose(fptr);
}
/**
 * Frees the results array
 * @param results array of strings
 * @param count number of strings
 */
void free_results(char** results, int count){
    for(int i = 0; i < count; i++){ 
        if(results[i] != NULL){
            free(results[i]);
        }
    }
    free(results);
}

/**
 * Assign CVS HEADEr to string array
 */
void assign_header(char* header_string, char** results){
    char buffer[LINE_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%s", header_string);
    results[0] = strdup(buffer);
}

/**
 * SKip the header of the CSV file
 * @param file file pointer
 */
void skip_header(FILE* file){
    char header[LINE_BUFFER_SIZE];
    fgets(header, LINE_BUFFER_SIZE, file);
}

/**
 * Random number generator in range [min, max]
 * @param min minimum value
 * @param max maximum value
 */
int getRandomInRange(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}