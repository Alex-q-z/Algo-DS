#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

static ht_item* ht_item_initializer(const char* k, const char* v){
  ht_item* i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);
  return i;
}

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

int main(){
  ht_hash_table* ht = ht_table_initializer(50); // size 50
  ht_table_freer(ht);
}
