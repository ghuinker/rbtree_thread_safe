#ifndef RBTREE_H
# define RBTREE_H

#include <stdio.h>

enum __attribute__ ((__packed__)) node_color {
  red,
  black
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

void insert_key(rbtree *t, int key);
void insert_node(rbtree *t, node_t node);
void print_tree(rbtree *t);

# endif
