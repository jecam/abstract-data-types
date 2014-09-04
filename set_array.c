/*
set ADT for dynamically sized arrays
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

/* typedef struct set set_t is defined in set.h */
struct set {
	/* TODO: define for arrays */
  int length;
  int capacity;
  int *data;
};

set_t *set_create(void)
{
  /* TODO: define for arrays */

  set_t *new_set; 
  new_set = safe_malloc(sizeof(set_t));
  new_set->length = 0;
  new_set->capacity = 1;
  new_set->data = safe_malloc(sizeof(int));
  return new_set;
}

void set_destroy(set_t *set)
{
  /* TODO: define for arrays */
  free(set->data);
  free(set);
  return;	
}

int set_insert(set_t *set, int new_val)
{
	/* TODO: define for arrays 
       insert in sorted order? */ 
  int i = 0;
  bool worked = false;
  int existing_value;
  /* if adding an entry will put us over capacity, double the capacity */
  if(set->length + 1 > set->capacity) {
    int new_cap = set->capacity * 2;
    set->data = safe_realloc(set->data, sizeof(int) * new_cap); 
    set->capacity = new_cap;
  }
  
  /* check that the new value doesn't already exist in our data */
  existing_value = set->data[0];
  while (i < set->length && existing_value != new_val) {
    existing_value = set->data[i++];
  }
  if (existing_value == new_val) {
    return worked;
  } else { /* add the new value */
    set->data[set->length] = new_val;
    set->length++;
    worked = true;
  }
  return worked;
}

int set_delete(set_t *set, int del_val)
{
  /* TODO: define for arrays */
  /* delete on a dynamically sized array needs to shift 
     all following entries down one key 
  */
  bool worked = false;
  int i = 0;
  int k = i;

  /* Could also use the search function for this ?*/
  for(; i < set->length; i++){
    if(set->data[i] == del_val) {
      worked = true;
      k = i;
      while(k < set->length - 1) {
        set->data[k] = set->data[k+1];
        k++;
      }
    }
  }
  if (worked)
    set->length--;
  return worked;	
}

int set_search(set_t *set, int search_val)
{
	/* TODO: define for arrays 
       returning as soon as found should be quicker 
       having an ordered set should speed things up too
    */
  
  bool found = false;
  int i = 0;
  
  for(; i< set->length; i++) {
    if(set->data[i] == search_val) {
      found = true;
      return found;
    }
  }
  return found;	
}

void set_print(set_t *set)
{
	/* optional, may help with testing */
  
  int i = 0;
  
  for(; i< set->length; i++) {
      printf("Array item %d value is %d\n", i, set->data[i]);
  }

  
}

