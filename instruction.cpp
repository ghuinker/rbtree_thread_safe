#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "instruction.h"

void set_inst_nodes(instruction *i, string s){
	string token, delimiter;
	inst_node_type type;
	inst_node_t node;
	int value;
	size_t pos, node_type_pos;

	value = 0;

	delimiter = ",";

	node_type_pos = pos = 0;
	while(s.length()){
		if((pos = s.find(delimiter)) != string::npos);
		else{
			pos = s.length()-1;
		}

		token = s.substr(0, pos);
		if((node_type_pos = token.find("b")) != string::npos){
			type = inst_black;
		}
		else if((node_type_pos = token.find("r")) != string::npos){
			type = inst_red;
		}
		else if(token.find("f") != string::npos){
			type = inst_leaf;
		}

		if(type != inst_leaf){
			value = stoi(token.substr(0, node_type_pos));
			node.value = value;
		}
		node.type = type;
		i->inst_nodes.push_back(node);

		s.erase(0, pos + delimiter.length());
	}
}

void set_actions(instruction *i, string s){
	string token, delimiter;
	int value;
	action_type type;
	action_t action;

	delimiter = ")";
	value = 0;

	size_t pos = 0;
	while ((pos = s.find(delimiter)) != string::npos) {

		token = s.substr(0, pos);
		if(token.find("insert") != string::npos) {
			type = act_insert;
		}
		else if(token.find("search") != string::npos) {
			type = act_search;
		}
		else if(token.find("delete") != string::npos) {
			type = act_delete;
		}
		value = stoi(token.substr(token.find("(") + 1, token.find(")")));

		action.type = type;
		action.value = value;

		i->actions.push_back(action);
		i->actions_length++;

		s.erase(0, pos + delimiter.length());
	}
}

int read_instruction(instruction *i, char *file){
	string line, init_tree, actions;
	ifstream f(file);
	uint16_t num_search_threads;
	uint16_t num_mod_threads;

	num_search_threads = num_mod_threads = 0;

	if(f) {
		while (getline( f, line )) {
			if(line.find("Search") != string::npos) {
				num_search_threads = stoi(line.substr(line.find(":") + 1));
			}
			else if(line.find("Modify") != string::npos) {
				num_mod_threads = stoi(line.substr(line.find(":") + 1));
			}
			else if(        line.find("search(") != string::npos ||
			                line.find("insert(") != string::npos ||
			                line.find("delete(") != string::npos
			                ) {
				actions = line;
			}
			else{
				if(line.length() > 0) {
					init_tree = line;
				}
			}
		}
		f.close();
	} else {
		cout << "Cannot find file\n";
		exit(-1);
	}

	i->num_search_threads = num_search_threads;
	i->num_mod_threads = num_mod_threads;
	set_inst_nodes(i, init_tree);
	set_actions(i, actions);


	return 0;
}
