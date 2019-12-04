#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "instruction.h"

int read_instruction(instruction *d, char *file){
	string line;
	ifstream f(file);

	if(f) {
		while (getline( f, line )) {
      cout << line;
		}
		f.close();
	} else {
		cout << "Cannot find file";
		exit(-1);
	}

  return 0;
}
