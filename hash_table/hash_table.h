typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  int size;
  int count;
  ht_item** items; // an array of pointers to items
} ht_hash_table;
