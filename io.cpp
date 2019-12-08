// #include <stdio.h>
#include <iostream>
#include <fstream>

#include "manager.h"
#include "rbtree.h"

using namespace std;

/*
        Functions: Recursively save the nodes from the tree
        Parameters:
                n: the node to save and recurse through.
								is_root: is the node the root node of the tree
                out: the outstream file to save to 
        Return Value: void
 */
void save_tree(node_t *node, bool is_root, std::ofstream& out)
{
	if (node == NULL) {
		out << (is_root ? "" : ",") << "f";
	}
	else{
		out << (is_root ? "" : ",") << node->key << (node->color == RED ? "r" : "b");
		save_tree(node->left, false, out);
		save_tree(node->right, false, out);
	}
}

/*
        Functions: Save the information to output.txt.
        Parameters:
                m: the manager.
								t: the tree
                execution_time: the execution time in microseconds
        Return Value: void
 */
void io_save(manager *m, rbtree *t, int execution_time){
  std::ofstream out;
  remove( "output.txt" );
  out.open("output.txt", std::ios::app);


	out << "Execution Time: " << execution_time << " microseconds" << endl;

	for(search_result_t *res: *m->search_results) {
		out << "search(" << res->action->value << ")-> " << (res->found ? "true:" : "false:") << ", performed by thread: " << res->thread_id << endl;
	}

  save_tree(t->root, true, out);
	out << endl;
  out.close();
}
