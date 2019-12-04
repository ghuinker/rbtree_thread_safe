#include <stdio.h>
#include <iostream>
using namespace std;

#include "rbtree.h"

void fix_tree(rbtree *t, node_t *node){

}

void print_tree(node_t *node)
{
    if (node == NULL)
        return;

    print_tree(node->left);
    cout << node->key << " ";
    print_tree(node->right);
}

void print_tree(rbtree *t)
{
    if (t->root == NULL)
        return;
    print_tree(t->root);
}


node_t* insert_node(node_t *root, node_t *node){
  if( root == NULL)
    return node;

  if(node->key < root->key){
    root->left = insert_node(root->left, node);
    root->left->parent = root;
  }
  else if(node->key > root->key){
    root->right = insert_node(root->right, node);
    root->right->parent = root;
  }
  return root;
}

void insert_node(rbtree *t, node_t *node){
  if(t->root == NULL){
    t->root = node;
  }
  else {
    insert_node(t->root, node);
    fix_tree(t, node);
  }
}

void insert_key(rbtree *t, int key){
  node_t *node = new node_t{key, NULL, NULL, NULL, red};

  insert_node(t, node);
}
