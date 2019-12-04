#include <stdio.h>
#include <iostream>
using namespace std;

#include "instruction.h"
#include "rbtree.h"

int main(int argc, char *argv[]){
  instruction i;
  rbtree t;
  char *load_file;

  load_file = NULL;

  //Debug
  if (argc < 2) {
    char tempStr[] = "test.txt";
    load_file = tempStr;
  } else {
    load_file = argv[1];
  }

  // Prod
  // if (argc < 2) {
  //   std::cout << "Please enter file name for tree initialization and actions.\n";
  //   exit(-1);
  // } else {
  //   load_file = argv[1];
  // }


  read_instruction(&i, load_file);
  for (inst_node_t x : i.inst_nodes){
    if(x.type != inst_leaf){
      cout << x.value << " ";
      insert_key(&t, x.value);
    }
  }

  // print_tree(&t);

}
