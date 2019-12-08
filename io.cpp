// #include <stdio.h>
#include <iostream>
#include <fstream>

#include "manager.h"
#include "rbtree.h"

using namespace std;

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

void io_save(manager *m, rbtree *t, int execution_time){
  std::ofstream out;
  remove( "output.txt" );
  out.open("output.txt", std::ios::app);


	out << "Execution Time: " << execution_time << endl;

	for(search_result_t *res: *m->search_results) {
		out << "search(" << res->action->value << ")-> " << (res->found ? "true:" : "false:") << ", performed by thread: " << res->thread_id << endl;
	}

  save_tree(t->root, true, out);
	out << endl;
  out.close();
}
