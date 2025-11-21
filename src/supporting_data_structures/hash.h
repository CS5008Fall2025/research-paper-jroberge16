#include <stdlib.h>
#include <stdint.h>
// source: https://www.geeksforgeeks.org/dsa/implementation-of-hash-table-in-c-using-separate-chaining/


typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct hashMap{
    int capacity;
    int number_of_elements;
    HashNode** table;
} hashMap;

uint32_t jenkins_one_at_a_time_hash(char *key);
void set_hash_node(HashNode* node, char* key, char* value);
hashMap* init_hash_map(int capcity);
void insert_hash(hashMap* mp, char* key, char* value);
void delete_hash(hashMap* map, char* key);
HashNode* get_hash_item(hashMap* map, char* key);
void free_hash_map(hashMap* map);



