#include <stdio.h>
#include <iostream>

#include "instruction.h"

int main(int argc, char *argv[]){
  instruction i;
  char *load_file;

  load_file = NULL;

  if (argc < 2) {
    std::cout << "Please enter file name for tree initialization and actions.\n";
    exit(-1);
  }

  load_file = argv[1];

  read_instruction(&i, load_file);


}
