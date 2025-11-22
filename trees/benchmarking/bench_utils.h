#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#define LINE_BUFFER_SIZE 20
#define TOTAL_INSERTS 5000
#define TOTAL_SEARCHES 10000
#define TOTAL_DELETES 10000
#include <stdio.h>

int get_next_number(FILE* file);
void append_lines_to_file(char** lines, char* file_name);

#endif