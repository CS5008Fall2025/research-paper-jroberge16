#ifndef MAIN_H
#define MAIN_H


typedef struct CommandLineArgs {
    int total_tree_size;
    int increment_tree_size;
    int batch_size;
    char dataStructure[16];
    char output_folder[256];
} CommandLineArgs;

CommandLineArgs processCommandLineArgs(int argc, char** argv);
int main(int argc, char** argv);

#endif