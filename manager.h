#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>

#include "instruction.h"
# include "rbtree.h"

class manager {
public:
  manager() : start_work(false), mod_action_index(0), search_action_index(0),
  actions_length(0), actions(0){};

  bool start_work;
  uint16_t mod_action_index;
  uint16_t search_action_index;
  uint16_t actions_length;

  std::vector<action_t> *actions;
};

void execute_work(manager *m, rbtree *t);
void init_manager(manager *m, rbtree *t, instruction *i);

# endif
