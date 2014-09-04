/*
set ADT for binary trees
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/



struct btree_node {
  int data;
  struct btree_node *left;
  struct btree_node *right;
};

/* typedef struct set set_t is defined in set.h */
struct set {
  /* TODO: define for binary trees */
  struct btree_node *root;
};

int r_insert_node(struct btree_node *root, struct btree_node *new);
int r_destroy_nodes(struct btree_node *node);
void r_print_node(struct btree_node *node);

set_t *set_create(void)
{
  /* TODO: define for binary trees */
  set_t *new_set = safe_malloc(sizeof(new_set));
  new_set->root = NULL;
  return new_set;
}

void set_destroy(set_t *set)
{
  struct btree_node *node = set->root;
  r_destroy_nodes(node);
  free(set);
  return;	
}

int r_destroy_nodes(struct btree_node *node)
{
  if(node->left != NULL)
    r_destroy_nodes(node->left);
  if(node->right != NULL)
    r_destroy_nodes(node->right);
  free(node); 
  return 1;
}

int set_insert(set_t *set, int new_val)
{
  int success = 0;
  struct btree_node *new_node;
  new_node = safe_malloc(sizeof(struct btree_node));
  new_node->data = new_val;
  new_node->left = NULL;
  new_node->right = NULL;

  if(set->root == NULL) {
    set->root = new_node;
    success = 1;
  } else {
    success = r_insert_node(set->root, new_node);
  }
  if(!success)
    free(new_node);
  return success;  
}

int r_insert_node(struct btree_node *root, struct btree_node *new_node)
{
  if(new_node->data < root->data) {
    if(root->left == NULL) {
      root->left = new_node;
      return 1;
    } else {
      return r_insert_node(root->left, new_node);
    }
  }

  if(new_node->data > root->data) {
    if(root->right == NULL) {
      root->right = new_node;
      return 1;
    } else {
      return r_insert_node(root->right, new_node);
    }
  }

  if(new_node->data == root->data) {
    return 0;
  }
  return 1;
}

int set_delete(set_t *set, int del_val)
{
 
  struct btree_node *current;
  struct btree_node *parent = NULL; 
  struct btree_node *node_for_deletion = NULL;

  if(set->root == NULL)
    return false;

  current = set->root;

  /* locate the node to be deleted */
  while(current != NULL) {
    if(current->data == del_val) {
      node_for_deletion = current;
      break;
    } else if (del_val < current->data) {
      parent = current;
      current = current->left;
    } else if (del_val > current->data) {
      parent = current;
      current = current->right;
    }
  }
  if(node_for_deletion == NULL)
    return false;

  /* if node to delete is a leaf, simply free its memory and set its 
  parent pointer to NULL */

  if(node_for_deletion->left == NULL && node_for_deletion->right == NULL) {
    if(parent == NULL) {  /* if the head node happens to be the only node */
      free(current);
      set->root = NULL;
      return true;
    } else {
      if (del_val < parent->data) {
        parent->left = NULL;
      } else if (del_val > parent->data) {
        parent->right = NULL;
      }
      free(current);
      return true;
    }
  }
  
  /* if the node has only the left or only the right but not both set to 
     non-NULL, link from parent to child and free its memory */
   
  if(node_for_deletion->left != NULL && node_for_deletion->right == NULL) {
    if(parent == NULL) { /* if the root node is being deleted */
      set->root = node_for_deletion->left;
      return true;
    } 
    if (parent->data < node_for_deletion->data) {
      parent->right = node_for_deletion->left;
    } else {
      parent->left = node_for_deletion->left;
    }
    free(node_for_deletion);
    return true;
  }

  if(node_for_deletion->right != NULL && node_for_deletion->left == NULL) {
    if(parent == NULL) { /* if the root node is being deleted */
      set->root = node_for_deletion->right;
      return true;
    }
    if(parent->data < node_for_deletion->data) {
      parent->right = node_for_deletion->right;
    } else {
      parent->left = node_for_deletion->right;
    }
    free(node_for_deletion);
    return true;
  }

  /* if the node has both children, find the highest value in the left subtree
     (i.e. go one level to the left and as far as possible to the right) and 
     promote its value to the "deleted" node, while actually deleting this one */
  
  if(node_for_deletion->left != NULL && node_for_deletion->right != NULL) {
    parent = current;
    current = node_for_deletion->left;
    while (current->right != NULL) {
      parent = current;
      current = current->right;
    }

    if(current->data < parent->data) {
      parent->left = NULL;
      if (current->left != NULL)
        parent->left = current->left;
    } else if (current->data > parent->data) {
      parent->right = NULL;
      if(current->left != NULL) {
        parent->right = current->left;
      }
    }
    node_for_deletion->data = current->data;
    free(current);
    return 1;    
  }
  return 0;
}

int set_search(set_t *set, int search_val)
{
  /* TODO: define for binary trees */
  struct btree_node *current;
  
  if(set->root == NULL)
    return false;

  current = set->root;

  while(search_val != current->data) {
    if(search_val < current->data) {
      if(current->left == NULL) {
        return 0;
      } else {
        current = current->left;
      }
    }
    if(search_val > current->data) {
      if(current->right == NULL) {
        return 0;
      } else {
        current = current->right;
      }
    }
  } /* end while */
  if(search_val == current->data)  
    return true;

  return false;	
}

void set_print(set_t *set)
{
  /* optional, may help with testing */
  r_print_node(set->root);
  
  return;
}

void r_print_node(struct btree_node *node){
  /* In-order print */
  
  if(node->left != NULL) {
    printf("%d", node->left->data);
  }
  else
    printf("NULL");
  printf("<-%d->", node->data);
  if(node->right != NULL) {
    printf("%d", node->right->data);
  }
  else
    printf("NULL");
  printf("\n");
  if(node->left != NULL)
    r_print_node(node->left);

  if(node->right != NULL)
    r_print_node(node->right);
  
  return;
}
