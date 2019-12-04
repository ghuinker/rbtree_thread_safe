#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "instruction.h"

int read_instruction(instruction *d, char *file){
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
			else if(	line.find("search(") != string::npos ||
								line.find("insert(") != string::npos ||
								line.find("delete(") != string::npos
							){
				actions = line;
			}
			else{
				if(line.length() > 0){
					init_tree = line;
				}
			}
		}
		f.close();
	} else {
		cout << "Cannot find file\n";
		exit(-1);
	}

	cout << num_search_threads << endl;
	cout << num_mod_threads << endl;
	cout << actions + "\n";
	cout << init_tree + "\n";


	return 0;
}
