// #include <stdio.h>
#include <iostream>
#include "manager.h"
#include "rbtree.h"
using namespace std;


void io_save(manager *m, rbtree *t, int execution_time){
	cout << "Execution Time: " << execution_time << endl;

	for(search_result_t *res: *m->search_results) {
		cout << "search(" << res->action->value << ")-> " << (res->found ? "true:" : "false:") << ", performed by thread: " << res->thread_id << endl;
	}

	print_tree(t);
}
