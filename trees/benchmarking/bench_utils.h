#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#define LINE_BUFFER_SIZE 150
#define TOTAL_INSERTS 50000
#define TOTAL_SEARCHES 10000
#define TOTAL_DELETES 10000
#include <stdio.h>

int get_next_number(FILE* file);
void append_lines_to_file(char** lines, char* file_name);
void free_results(char** results, int count);
void assign_header(char* header_string, char** results);
void skip_header(FILE* file);
int getRandomInRange(int min, int max);
#endif