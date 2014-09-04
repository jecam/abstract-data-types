/*
set ADT for linked lists
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

struct list_node {
	struct list_node *next;
	int val;
};

/* typedef struct set set_t is defined in set.h */
struct set {
	struct list_node *head;
};

/* set_create() */
set_t *set_create(void)
{
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	new_set->head = NULL;
	return new_set;
}

/* set_destroy() */
void set_destroy(set_t *set)
{
	struct list_node *node;

	node = set->head;
	while (node) {
		struct list_node *del_node = node;
		node = node->next;
		free(del_node);
	}

	free(set);	
	return;	
}

/* set_insert() */
int set_insert(set_t *set, int new_val)
{
	struct list_node **node;
	struct list_node *new_node;

	node = &set->head;
	while (*node && (*node)->val < new_val) {
		node = &((*node)->next);
	}
	if (*node && (*node)->val == new_val) {
		return 0;	/* this is a repeat */
	}
		/* new_val is not in list, make a new node */
	new_node = safe_malloc(sizeof(struct list_node));
	new_node->val = new_val;
	new_node->next = *node;
	*node = new_node;

	return 1;
}

/* set_delete() */
int set_delete(set_t *set, int del_val)
{
	struct list_node **node;

	node = &set->head;
	while (*node && (*node)->val < del_val) {
		node = &((*node)->next);
	}
	if (*node && (*node)->val == del_val) {
		struct list_node *del_node = *node;
		*node = (*node)->next;
		free(del_node);
		return 1;
	}

	return 0;	
}

/* set_search() */
int set_search(set_t *set, int search_val)
{
	struct list_node *node;

	node = set->head;
	while(node && node->val < search_val) {
		node = node->next;
	}
	if (node && node->val == search_val) {
		return 1;
	}

	return 0;	
}

/* set_print() */
void set_print(set_t *set)
{
	struct list_node *node;
	node = set->head;
	while (node) {
		printf("%d", node->val);
		node = node->next;
		if (node) {
			printf("->");
		} else {
			printf("\n");
		}
	}	
}

