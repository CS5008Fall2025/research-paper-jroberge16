#include <stdio.h>
#include "benchmarking/avl_benchmarks.h"
#include "benchmarking/bin_benchmarks.h"









int main() {
    printf("Running Benchmarks for Trees\n");
    run_avl_benchmarks();
    run_bin_benchmarks();
    return 0;
}