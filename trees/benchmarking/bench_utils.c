#include <stdio.h>
#include <stdlib.h>

#include "bench_utils.h"




int get_next_number(FILE* file){
    char buffer[LINE_BUFFER_SIZE];
    if(fgets(buffer, LINE_BUFFER_SIZE, file) != NULL){
        int number = atoi(buffer);
        return number;
    } else{
        return -1;
    }
}


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
