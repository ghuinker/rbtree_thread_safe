#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>

#include "instruction.h"
# include "rbtree.h"


class manager {
public:
manager() : start_work(false),
  mod_action_index(0), search_action_index(0),
	mod_actions_length(0), search_actions_length(0),
  mod_actions(0), search_actions(0)
  {};

bool start_work;
uint16_t mod_action_index,search_action_index;
uint16_t mod_actions_length, search_actions_length;

std::vector<action_t> mod_actions;
std::vector<action_t> search_actions;
sem_t *mod_sem, *search_sem;
};

void execute_work(manager *m, rbtree *t, instruction *i);
void init_manager(manager *m, rbtree *t, instruction *i);

# endif
