#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>
#include <queue>

#include "instruction.h"
# include "rbtree.h"


class manager {
public:
manager() : start_work(false),
  mod_actions(0), search_actions(0)
  {};

bool start_work;

queue<action_t *> *mod_actions;
queue<action_t *> *search_actions;
sem_t *mod_sem, *search_sem;
};

void execute_work(manager *m, rbtree *t, instruction *i);
void init_manager(manager *m, rbtree *t, instruction *i);

# endif
