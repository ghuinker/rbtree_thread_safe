#ifndef MANAGER_H
# define MANAGER_H

#include <stdio.h>

#include "instruction.h"

class manager {
public:
  manager() : mod_action_index(0), search_action_index(0), start_work(false){};

  bool start_work;
  uint16_t mod_action_index;
  uint16_t search_action_index;
};

void execute_work(manager *m);
void init_threads(manager *m, instruction *i);

# endif
