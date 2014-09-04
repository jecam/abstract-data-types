/*
set ADT for hash tables with separate chaining
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

#define DEFAULT_HASH_SIZE 127
#define HASH_FACTOR 3571
#define HASH_LIMIT 1200000
unsigned int hash_calc(set_t *set, int value);

/* typedef struct set set_t is defined in set.h */
struct set {
  int size;
  int items;
  struct entry_t **table;
};

typedef struct entry_t {
  unsigned int key;
  int value;
  struct entry_t *next;
} entry_t;

set_t *set_create(void)
{
  set_t *set;
  set = safe_malloc(sizeof(set_t));
  
  set->size = DEFAULT_HASH_SIZE;
  set->items = 0;
  set->table = (entry_t **)safe_malloc(set->size * sizeof(entry_t*));
  int i;
  for(i = 0; i < set->size; i++) {
    set->table[i] = NULL;
  }
  return set;
}

void set_destroy(set_t *set)
{
  int i;
  entry_t *entry;
  for(i = 0; i < set->size; i++){
    entry = set->table[i];
    while(entry){
      struct entry_t *del_entry = entry;
      entry = entry->next;
      free(del_entry);
    }
  }
  free(set->table);
  free(set);
  return;	
}

int set_insert(set_t *set, int new_val)
{
  unsigned int key = hash_calc(set, new_val);
  struct entry_t **entry;
  struct entry_t *new_entry;
  
  entry = &set->table[key];
  
  while (*entry && (*entry)->value < new_val){
    entry = &((*entry)->next);
  }
  /* this is a duplicate entry */
  if (*entry && (*entry)->value == new_val) {
    return 0;
  }
  
  new_entry = safe_malloc(sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = new_val;
  new_entry->next = *entry;
  
  *entry = new_entry;

  set->items++;

  return 1;
}

int set_delete(set_t *set, int del_val)
{
  unsigned int key = hash_calc(set, del_val);
  struct entry_t **entry;
  
  entry = &set->table[key];
  while (*entry && (*entry)->value < del_val) {
    entry = &((*entry)->next);
  }
  if (*entry && (*entry)->value == del_val) {
    struct entry_t *del_entry = *entry;
    *entry = (*entry)->next;
    free(del_entry);
    set->items--;
    return 1;
  }
  return 0;
}

int set_search(set_t *set, int search_val)
{
  unsigned int key = hash_calc(set, search_val);
  struct entry_t *entry;

  if(set->table[key] == NULL)
    return false;
  
  entry = set->table[key];
  
  while(entry && entry->value < search_val) {
    entry = entry->next;
  }
  if (entry && entry->value == search_val) {
    return 1;
  }
  
  return 0;	
}

void set_print(set_t *set)
{
	/* optional, may help with testing */
  int i;
  for(i = 0; i < set->size; i++) {
    struct entry_t *entry;
    printf("Hash %d -> { ", i);
    entry = set->table[i];
    while(entry) {
      printf("%d, ", entry->value);
      entry = entry->next;
    }
    printf(" }\n");
  }
  printf("\n");
}


unsigned int hash_calc(set_t *set, int value) {
  unsigned long int result = value;
  /* For large enough input values, this calculation is too much to store in 
     even an unsigned long 32bit int. Not a perfect workaround but helps
     evenly distribute values across the table while still being somewhat 
     predictable.
  */
  if(result < HASH_LIMIT)
    result = (value * HASH_FACTOR);

  result = (unsigned int)(result % set->size);
  return result;
}
