#include <stdio.h>
#include <iostream>
using namespace std;

#include "rbtree.h"

void rotate_left(node_t *&root, node_t *&node)
{
	node_t *temp = node->right;
	node->right = temp->left;

	if (node->right != NULL) {
		node->right->parent = node;
	}

	temp->parent = node->parent;

	if (node->parent == NULL) {
		root = temp;
	}
	else if (node == node->parent->left) {
		node->parent->left = temp;
	}
	else{
		node->parent->right = temp;
	}

	temp->left = node;
	node->parent = temp;
}


void rotate_right(node_t *&root, node_t *&node){
	node_t *temp = node->left;
	node->left = temp->right;

	if (node->left != NULL) {
		node->left->parent = node;
	}

	temp->parent = node->parent;

	if (node->parent == NULL) {
		root = temp;
	}
	else if (node == node->parent->left) {
		node->parent->left = temp;
	}
	else{
		node->parent->right = temp;
	}

	temp->right = node;
	node->parent = temp;
}

void fix_tree(node_t *&root, node_t *&node){

}

node_t* insert_node(node_t *&root, node_t *&node){
	if( root == NULL) {
		root = node;
	}
	if(node->key < root->key) {
		root->left = insert_node(root->left, node);
		root->left->parent = root;
	}
	else if(node->key > root->key) {
		root->right = insert_node(root->right, node);
		root->right->parent = root;
	}
	return root;
}

void insert_node(rbtree *t, node_t *node){
	insert_node(t->root, node);
	fix_tree(t->root, node);
}

void insert_key(rbtree *t, int key){
	node_t *node = new node_t{key, NULL, NULL, NULL, red};

	insert_node(t, node);
}

void print_tree(node_t *node)
{
	if (node == NULL)
		return;

	cout << node->key << " ";
	print_tree(node->left);
	print_tree(node->right);
}

void print_tree(rbtree *t)
{
	print_tree(t->root);
}
