#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>
#include <queue>
#include <vector>

#include "instruction.h"
# include "rbtree.h"

typedef struct search_result {
  bool found;
  uint16_t thread_id;
  action_t *action;
} search_result_t;

//The manager responsible for information regaurding the threading.
class manager {
public:
manager() :mod_actions(0), search_actions(0)
  {};

std::queue<action_t *> *mod_actions;
std::queue<action_t *> *search_actions;
sem_t *mod_sem, *search_sem, *result_sem;
std::vector<search_result_t *> *search_results;
};

void execute_work(manager *m, rbtree *t, instruction *i);
void init_manager(manager *m, rbtree *t, instruction *i);

# endif
