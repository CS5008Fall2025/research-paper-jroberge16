#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hash.h"



void test_hash() {
    hashMap* map = init_hash_map(5);
    assert(map != NULL);
    assert(map->capacity == 5);
    assert(map->number_of_elements == 0);
    printf("\t✅ Hash Map Initialization\n");
    
    insert_hash(map, "1", "1");
    assert(strcmp(get_hash_item(map, "1")->value, "1") == 0);
    printf("\t✅ insert and getter\n");

    delete_hash(map, "1");
    assert(get_hash_item(map, "1") == NULL);
    printf("\t✅ delete\n");

    insert_hash(map, "1", "1");
    insert_hash(map, "8", "1");
    insert_hash(map, "7", "1");
    insert_hash(map, "6", "1");
    insert_hash(map, "5", "1");
    insert_hash(map, "4", "1");
    insert_hash(map, "3", "1");
    insert_hash(map, "2", "1");
    assert(map->capacity > 5);
    printf("\t✅ increase capacity\n");

    free_hash_map(map);    
}


int main() {
    printf("🧪 Testing Hash Implementation\n");
    test_hash();
    printf("🥳 ALL TESTS PASSED\n");
    return 0;
}


