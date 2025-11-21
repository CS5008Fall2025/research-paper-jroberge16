#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#include "hash.h"


uint32_t jenkins_one_at_a_time_hash(char *key)
{
    uint32_t hash, c;
    hash = 0;
    while ((c = *key++))
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void set_hash_node(HashNode* node, char* key, char* value) {
    node->key = key;
    node->value = value;
    node->next = NULL;

}

hashMap* init_hash_map(int capcity){
    hashMap* map = (hashMap*)malloc(sizeof(hashMap));
    map->capacity = capcity;
    map->number_of_elements = 0;
    map->table = (HashNode**)calloc(capcity, sizeof(HashNode*));
    return map;
}

void __increase_hash_map_capacity(hashMap* map){
    int new_capcity = map->capacity * 2;
    HashNode** bew_table = (HashNode**)realloc(map->table,new_capcity * sizeof(HashNode*));
    if(bew_table == NULL){
        perror("Failed to allocate hash map");
        exit(EXIT_FAILURE);
    }
    map->table = bew_table;
    map->capacity = new_capcity;
}

void insert_hash(hashMap* mp, char* key, char* value)
{   
    if(mp->capacity/.75 < mp->number_of_elements){
        __increase_hash_map_capacity(mp);
    }


    int index = jenkins_one_at_a_time_hash(key)% mp->capacity;
    HashNode *new_node = (HashNode*)malloc(sizeof(HashNode));
    if(new_node == NULL){
        perror("Failed to allocate min heap");
        exit(EXIT_FAILURE);
    }
    set_hash_node(new_node, key, value);

    if (mp->table[index] == NULL){
        mp->table[index] = new_node;
    }
    else {
        new_node->next = mp->table[index];
        mp->table[index] = new_node;
    }
    mp->number_of_elements++;
    return;
}

void delete_hash(hashMap* map, char* key){
    int index = jenkins_one_at_a_time_hash(key) % map->capacity;
    HashNode* curr = map->table[index];
    HashNode* prev = NULL;

    while(curr != NULL){
        if(strcmp(curr->key, key) == 0){
            if(prev == NULL){
                map->table[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}


HashNode* get_hash_item(hashMap* map, char* key){
    int index = jenkins_one_at_a_time_hash(key) % map->capacity;
    HashNode* curr = map->table[index];

    while(curr != NULL){
        if(curr->key == key){
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}


void free_hash_map(hashMap* map){
    for(int i = 0; i < map->capacity; i++){
        HashNode* curr = map->table[i];
        while(curr != NULL){
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(map->table);
    free(map);
}