#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>

#include "instruction.h"
# include "rbtree.h"

typedef struct search_obj {
	rbtree *t;
	manager *m;
	node_t *result_node;
	pthread_t thread_id;
} search_obj_t;

typedef struct mod_obj {
	rbtree *t;
	manager *m;
} mod_obj_t;

class manager {
public:
manager() : start_work(false),
  mod_action_index(0), search_action_index(0),
	mod_actions_length(0), search_actions_length(0),
  mod_actions(0), search_actions(0), mod_objects(0), search_objects(0),
  {};

bool start_work;
uint16_t mod_action_index,search_action_index;
uint16_t mod_actions_length, search_actions_length;

std::vector<action_t> mod_actions;
std::vector<action_t> search_actions;
std::vector<mod_obj_t> mod_objects;
std::vector<search_obj_t> search_objects;
sem_t *mod_sem, *search_sem;
};

void execute_work(manager *m, rbtree *t);
void init_manager(manager *m, rbtree *t, instruction *i);

# endif
