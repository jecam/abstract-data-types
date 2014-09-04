/*
set.h - set ADT interface header file
*/

#ifndef SET_H
#define SET_H

typedef struct set set_t;

/* initialise a new set data structure */
set_t *set_create(void);

/* free the set data structure */
void set_destroy(set_t *set);

/* insert a value into the set, return 1 if new, 0 if repeat */
int set_insert(set_t *set, int val);

/* remove a value from the set, return 1 if removed, 0 if missing */
int set_delete(set_t *set, int val);

/* search for a value, return 1 if present, 0 if absent */ 
int set_search(set_t *set, int val);

/* additional/optional functions */

/* print out the internal set structure, may aid debugging */
void set_print(set_t *set);


#endif	/* include guard */
