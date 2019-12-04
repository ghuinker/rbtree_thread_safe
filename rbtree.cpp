#include <stdio.h>
#include <iostream>
using namespace std;

#include "rbtree.h"

void print_tree(node_t *node, bool is_root)
{
	if (node == NULL) {
		cout << (is_root ? "" : ",") << "f";
		return;
	}
	else{
		cout << (is_root ? "" : ",") << node->key << (node->color == RED ? "r" : "b");
    print_tree(node->left, false);
    print_tree(node->right, false);
	}
}

void print_tree(rbtree *t)
{
	print_tree(t->root, true);
	cout << endl;
}

node_t* set_node(instruction *i, node_t *parent, uint16_t *index){
	node_t *node;
	++(*index);
	if(i->inst_nodes[(*index)].type == inst_leaf) {
		return NULL;
	}

	node = new node_t{i->inst_nodes[(*index)].value, NULL, NULL, parent, (i->inst_nodes[(*index)].type == inst_black ? RED : BLACK)};

	node->left = set_node(i, node, index);
	node->right = set_node(i, node, index);

	return node;
}

void init_tree(rbtree *t, instruction *i){
	uint16_t index;

	if(i->inst_nodes.size() == 0 || i->inst_nodes[0].type == inst_leaf) {
		return;
	}
	t->root = new node_t{i->inst_nodes[0].value, NULL, NULL, NULL, (i->inst_nodes[0].type == inst_black ? RED : BLACK)};

	index = 0;
	t->root->left = set_node(i, t->root, &index);
	t->root->right = set_node(i, t->root, &index);
	// cout << index << endl;
}

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

/*
   Insert Functions
 */
void insert_fix_tree(node_t *&root, node_t *&node){
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

/*
   Delete Functions
 */
bool has_red_child(node_t *node){
	if(node->left != NULL) {
		if(node->left->color == RED) {
			return true;
		}
	}
	if(node->right != NULL) {
		if(node->right->color == RED) {
			return true;
		}
	}
	return false;
}

bool on_left(node_t *node){
	return node->parent->left == node;
}

node_t* sibling_node(node_t *node){
	if(node->parent == NULL) {
		return NULL;
	}
	if(on_left(node)) {
		return node->parent->right;
	}
	else{
		return node->parent->left;
	}
}

void fix_double_back(node_t *&root, node_t *&node) {
	node_t *sibling, *parent;
	if (node == root) {
		return;
	}

	sibling = sibling_node(node);
	parent = node->parent;

	if (sibling == NULL) {
		// No sibiling, double black pushed up
		fix_double_back(root, parent);
	} else {
		if (sibling->color == RED) {
			// Sibling red
			parent->color = RED;
			sibling->color = BLACK;
			if (on_left(sibling)) {
				rotate_right(root, parent);
			} else {
				rotate_left(root, parent);
			}
			fix_double_back(root, node);
		} else {
			// Sibling black
			if (has_red_child(sibling)) {
				// at least 1 red children
				if (sibling->left != NULL && sibling->left->color == RED) {
					if (on_left(sibling)) {
						// left left
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rotate_right(root, parent);
					} else {
						// right left
						sibling->left->color = parent->color;
						rotate_right(root, sibling);
						rotate_left(root, parent);
					}
				} else {
					if (on_left(sibling)) {
						// left right
						sibling->right->color = parent->color;
						rotate_left(root, sibling);
						rotate_right(root, parent);
					} else {
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						rotate_left(root,parent);
					}
				}
				parent->color = BLACK;
			} else {
				// 2 black children
				sibling->color = RED;
				if (parent->color == BLACK)
					fix_double_back(root, parent);
				else
					parent->color = BLACK;
			}
		}
	}
}


node_t* replacement_node(node_t *&node){
	node_t *temp;
	if(node->left != NULL && node->right != NULL) {
		temp = node->left;
		while(temp->right != NULL) {
			temp = temp->right;
		}
		return temp;
	}
	if(node->left == NULL && node->right == NULL) {
		return NULL;
	}
	if(node->left != NULL) {
		return node->left;
	} else {
		return node->right;
	}
}

void delete_node(node_t *&root, node_t *&node){
	node_t *replace_node, *parent;

	replace_node = replacement_node(node);
	parent = node->parent;

	if (replace_node == NULL) {
		if (node  == root) {
			root = NULL;
		}
		else {
			if ((replace_node == NULL || replace_node->color == BLACK) && (node->color == BLACK)) {
				fix_double_back(root, node);
			} else {
				if (sibling_node(node) != NULL)
					sibling_node(node)->color = RED;
			}
			if (on_left(node)) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
		}
		delete node;
		return;
	}

	if (node->left == NULL || node->right == NULL) {
		// node  has 1 child
		if (node  == root) {
			// node  is root, assign the value of replace_node to node, and delete replace_node
			node->key = replace_node->key;
			node->left = node->right = NULL;
			delete replace_node;
		} else {
			// Detach node  from tree and move replace_node up
			if (on_left(node)) {
				parent->left = replace_node;
			} else {
				parent->right = replace_node;
			}
			delete node;
			replace_node->parent = parent;
			if ((replace_node == NULL || replace_node->color == BLACK) && (node->color == BLACK)) {
				// replace_node and node  both black, fix double black at replace_node
				fix_double_back(root, replace_node);
			} else {
				replace_node->color = BLACK;
			}
		}
		return;
	}

	// node  has 2 children, swap values with successor and recurse
	swap(replace_node->key, node->key);
	delete_node(root, replace_node);
}

void delete_fix_tree(node_t *&root, node_t *&node){

}

node_t* search_node(node_t *node, int key){
	node_t *temp;
	if(node == NULL)
		return NULL;
	if(node->key == key) {
		return node;
	}
	if((temp = search_node(node->left, key)) == NULL) {
		temp = search_node(node->right, key);
	}

	return temp;
}

/*
   CRITICAL MAIN Functions
 */
void insert_node(rbtree *t, node_t *node){
	insert_node(t->root, node);
	insert_fix_tree(t->root, node);
}

void delete_node(rbtree *t, node_t *node){
	if(t->root == NULL)
		return;

	delete_node(t->root, node);
	// delete_fix_tree(t->root, node);
}



/*
   CRITICAL Init Functions
 */
void insert_key(rbtree *t, int key){
	node_t *node = new node_t{key, NULL, NULL, NULL, RED};
	insert_node(t, node);
}

node_t* search_tree(rbtree *t, int key){
	return search_node(t->root, key);
}

void delete_key(rbtree *t, int key){
	if(t->root == NULL)
		return;

	node_t *node = search_tree(t, key);
	delete_node(t, node);
}
