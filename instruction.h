#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include <string>
# include <vector>

enum __attribute__ ((__packed__)) action_type {
	act_insert,
	act_search,
	act_delete
};

enum __attribute__ ((__packed__)) inst_node_type {
	inst_red,
	inst_black,
	inst_leaf
};

typedef struct action {
	action_type type;
	int value;
} action_t;

typedef struct inst_node {
	inst_node_type type;
	int value;
} inst_node_t;

class instruction {
public:
instruction() :  num_search_threads(0), num_mod_threads(0),actions_length(0), inst_nodes(0),
	actions(0){};
uint16_t num_search_threads;
uint16_t num_mod_threads;
uint16_t actions_length;
std::vector<inst_node_t> inst_nodes;
std::vector<action_t *> actions;
};

int read_instruction(instruction *i, char *file);

#endif
