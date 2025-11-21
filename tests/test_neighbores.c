#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>


#include "neighbores.h"



void test_neighbors() {
    Neighbors* nh =  neighbor_list_int(50);
    assert(nh->connections->capacity==50);
    printf("\t Passed initialization\n");

    add_neighbor(nh, 5);
    add_neighbor(nh, 2);
    add_neighbor(nh, 4);

    assert(nh->connections->count==3);
    printf("\t Passed insertion\n");
    free_neighbors(nh);
}





int main() {
    printf("🧪 Testing Neighbors Implementation\n");
    test_neighbors();
    printf("🥳 ALL TESTS PASSED\n");
    return 0;
}