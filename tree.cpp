#include <stdio.h>
#include <iostream>

#include "instruction.h"

int main(int argc, char *argv[]){
  instruction i;
  char *load_file;

  load_file = NULL;

  if (argc < 2) {

    //DEBUG
    char tempStr[] = "test.txt";
    load_file = tempStr;


    // PROD
    // std::cout << "Please enter file name for tree initialization and actions.\n";
    // exit(-1);
  } else {
    //Make as default!!!!
    load_file = argv[1];
  }


  read_instruction(&i, load_file);


}
