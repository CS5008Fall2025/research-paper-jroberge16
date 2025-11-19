#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "vector.h"

// Test structure for testing with complex types
typedef struct {
    int id;
    char name[50];
    double value;
} TestStruct;

void test_vector(){
    // create a vector
    Vector* vector = create_vector(sizeof(TestStruct), 10);
    assert(vector != NULL);
    assert(vector->single_element_size == sizeof(TestStruct));
    assert(vector->capacity == 10);
    assert(vector->count == 0);
    printf("\t✅ test_make_vector passed\n");

    // append elements to vector
    append_vector_element(vector, &(TestStruct){1, "Test1", 1.0});
    append_vector_element(vector, &(TestStruct){2, "Test2", 2.0});
    append_vector_element(vector, &(TestStruct){3, "Test3", 3.0});
    append_vector_element(vector, &(TestStruct){4, "Test4", 4.0});

    assert(vector->count == 4);
    assert(((TestStruct*)vector->items)[0].id == 1);
    assert(strcmp(((TestStruct*)vector->items)[0].name, "Test1") == 0);
    assert(((TestStruct*)vector->items)[0].value == 1.0);
    assert(((TestStruct*)vector->items)[3].value == 4.0);

    printf("\t✅ append elements to a vector\n");




    // insert in location
    insert_vector_element(vector, 0, &(TestStruct){99999, "insert_test_1", 9.9});
    insert_vector_element(vector, 1, &(TestStruct){99999, "insert_test_2", 9.9});
    insert_vector_element(vector, 3, &(TestStruct){99999, "insert_test_3", 9.9});

    assert(vector->count == 7);
    assert(((TestStruct*)vector->items)[0].id == 99999);
    assert(((TestStruct*)vector->items)[1].id == 99999);
    assert(((TestStruct*)vector->items)[3].id == 99999);
    printf("\t✅ insert values\n ");

    //remove vector Elements
    remove_vector_element(vector, 3);
    remove_vector_element(vector, 1);
    remove_vector_element(vector, 0);

    assert(vector->count == 4);
    assert(((TestStruct*)vector->items)[0].id == 1);
    assert(((TestStruct*)vector->items)[1].id == 2);
    assert(((TestStruct*)vector->items)[2].id == 3);
    printf("\t✅ remove values\n ");

    // set vector element
    set_vector_element(vector, 0, &(TestStruct){999, "set_test", 5.5});
    assert(((TestStruct*)vector->items)[0].id == 999);
    printf("\t✅ set values\n ");

    // free vector
    free_vector(vector);
    printf("\t✅ free vector\n ");
}




int main() {
    printf("🧪 Testing Vector Implementation\n");
    test_vector();
    printf("🥳 ALL TESTS PASSED\n");




    

    return 0;
}