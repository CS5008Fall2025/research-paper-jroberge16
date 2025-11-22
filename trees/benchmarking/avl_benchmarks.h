#ifndef AVL_BENCHMARKS_H
#define AVL_BENCHMARKS_H

#include "bench_utils.h"



#include <stdio.h>

typedef void (*FuncPtr)(int);
typedef void (*FuncPtr)(int);


typedef struct {
    char* funtction_name;
    char* tree_type;

    int value;
    FuncPtr func;
} MyStruct;


void run_avl_benchmarks();
void assign_header(char* header_string, char** results);
void skip_header(FILE* file);
void free_results(char** results, int count);





#endif