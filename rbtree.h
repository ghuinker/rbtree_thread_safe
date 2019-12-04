#ifndef RBTREE_H
# define RBTREE_H

#include <stdio.h>

#include "instruction.h"

enum __attribute__ ((__packed__)) node_color {
  RED,
  BLACK
};

typedef struct node {
  int key;
  node *left;
  node *right;
  node *parent;
  node_color color;
} node_t;

class rbtree {
  public:
    rbtree(): root{0} {};

    node_t *root;
};

void init_tree(rbtree *t, instruction *i);
void insert_key(rbtree *t, int key);
void delete_key(rbtree *t, int key);
node_t* search_tree(rbtree *t, int key);
void print_tree(rbtree *t);

# endif
