#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_item_initializer(const char* k, const char* v){
  ht_item* i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);
  return i;
}

// initialize the hash table
ht_hash_table* ht_table_initializer(const int ht_size){
  ht_hash_table* ht = malloc(sizeof(ht_hash_table));
  ht->size = ht_size;
  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
  return ht;
}

static void ht_item_freer(ht_item* i){
  free(i->key);
  free(i->value);
  free(i);
}

// free the hash table
void ht_table_freer(ht_hash_table* ht){
  for(int i = 0; i < ht->size; i++){
    ht_item* item = ht->items[i];
    if(item != NULL){
      ht_item_freer(item);
    }
  }
  free(ht->items);
  free(ht);
}

// a generic hash function
static int ht_hash_func(const char* s, const int a, const int m){
  long hash = 0;
  int len_str = strlen(s);
  for(int i = 0; i < len_str; i++){
    hash += (long)pow(a, len_str - (i+1)) * s[i];
    hash = hash % m;
  }
  return (int)hash;
}

// handle collisions using open addressing + double hashing
// return hash value
static int ht_get_hash(const char* s, const int num_buc, const int attempt){
  int hash_a = ht_hash_func(s, HT_PRIME_1, num_buc);
  int hash_b = ht_hash_func(s, HT_PRIME_2, num_buc);
  int res = (hash_a + (attempt * (hash_b + 1))) % num_buc; // "+1":in case hb=0
  return res;
}

// insert
void ht_insert(ht_hash_table* ht, const char* key, const char* value){
  ht_item* new_item = ht_item_initializer(key, value);
  int hash_value = ht_get_hash(new_item->key, ht->size, 0); // index
  ht_item* curr_item = ht->items[hash_value];
  int i = 1;
  while(curr_item != NULL && cur_item != &HT_DELETED_ITEM){ 
    // iterates until a bucket is empty
    hash_value = ht_get_hash(item->key, ht->size, i);
    curr_item = ht->items[hash_value];
    i++;
  }
  ht->items[hash_value] = new_item;
  ht->count++;
}

// search
char* ht_search(ht_hash_table* ht, const char* key){
  int hash_value = ht_get_hash(key, ht->size, 0);
  ht_item* item = ht->items[hash_value];
  int i = 1;
  while(item != NULL){
    if(item != &HT_DELETED_ITEM){
      if(strcmp(item->key, key) == 0){
	return item->value;
      }
    }
    hash_value = ht_get_hash(key, ht->size, i);
    item = ht->items[hash_value];
    i++;    
  }
  return NULL; // key not found
}

// delete
void ht_delete(ht_hash_table* ht, const char* key){
  int hash_value = ht_get_hash(key, ht->size, 0); // index
  ht_item* item = ht->items[hash_value];
  int i = 1;
  while(item != NULL){
    if(item != &HT_DELETED_ITEM){
      if(strcmp(item->key, key) == 0){
	ht_item_freer(item);
	ht->items[hash_value] = &HT_DELETED_ITEM;
      }
    }
    hash_value = ht_get_hash(key, ht->size, i);
    item = ht->items[hash_value];
    i++;
  }
  ht->count--;
}

int main(){
  ht_hash_table* ht = ht_table_initializer(50); // size 50
  ht_table_freer(ht);
}
