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
	node_t *parent_node = NULL;
	node_t *grand_parent_node = NULL;

	while ((node != root) && (node->color != BLACK) &&
	       (node->parent->color == RED))
	{

		parent_node = node->parent;
		grand_parent_node = node->parent->parent;

    //A: Parent is left of child of grand-parent
		if (parent_node == grand_parent_node->left)
		{

			node_t *uncle_node = grand_parent_node->right;

      //1: the uncle of node is red
			if (uncle_node != NULL && uncle_node->color == RED)
			{
				grand_parent_node->color = RED;
				parent_node->color = BLACK;
				uncle_node->color = BLACK;
				node = grand_parent_node;
			}

			else
			{
        //2: Left Rotation
				if (node == parent_node->right)
				{
					rotate_left(root, parent_node);
					node = parent_node;
					parent_node = node->parent;
				}
        //3: Right Rotate
				rotate_right(root, grand_parent_node);
				swap(parent_node->color, grand_parent_node->color);
				node = parent_node;
			}
		}
    //B: Parent is right of child of grand-parent
		else
		{
			node_t *uncle_node = grand_parent_node->left;

      //1: uncle is red
			if ((uncle_node != NULL) && (uncle_node->color == RED))
			{
				grand_parent_node->color = RED;
				parent_node->color = BLACK;
				uncle_node->color = BLACK;
				node = grand_parent_node;
			}
			else
			{
        //2: right rotate
				if (node == parent_node->left)
				{
					rotate_right(root, parent_node);
					node = parent_node;
					parent_node = node->parent;
				}
        //3: left rotate
				rotate_left(root, grand_parent_node);
				swap(parent_node->color, grand_parent_node->color);
				node = parent_node;
			}
		}
	}
  root->color = BLACK;
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
	node_t *node = new node_t{key, NULL, NULL, NULL, RED};

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
