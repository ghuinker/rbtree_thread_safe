#ifndef RBTREE_H
# define RBTREE_H

#include <stdio.h>
#include <semaphore.h>

#include "instruction.h"

enum __attribute__ ((__packed__)) node_color {
  RED,
  BLACK
};

//A node the the Rbtree
typedef struct node {
  int key;
  node *left;
  node *right;
  node *parent;
  node_color color;
} node_t;

//The RBTree object.
class rbtree {
  public:
    rbtree(): root{0}, reader_count(0){};

    node_t *root;
    uint16_t reader_count;
    sem_t *x, *wsem;
};

void signal_wsem(rbtree *t);
void wait_wsem(rbtree *t);
void signal_x(rbtree *t);
void wait_x(rbtree *t);
void init_sems(rbtree *t);
void init_tree(rbtree *t, instruction *i);
void insert_key(rbtree *t, int key);
void delete_key(rbtree *t, int key);
node_t* search_tree(rbtree *t, int key);
void print_tree(rbtree *t);

# endif
