#include <stdio.h>
#include <iostream>

#include "instructions.h"


int main(int argc, char *argv[]){
  instruction i;
  char *load_file;

  load_file = NULL;

  if (argc < 2) {
    std::cout << "Please enter file name for tree initialization and actions.\n";
    exit(-1);
  }

  load_file = argv[1];
  std::cout << load_file;
  // read_input_insturctions(&i, input_file);


}
