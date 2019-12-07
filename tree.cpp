#include <stdio.h>
#include <iostream>
#include <chrono>
using namespace std;

#include "instruction.h"
#include "rbtree.h"
#include "manager.h"

int main(int argc, char *argv[]){
  instruction i;
  rbtree t;
  manager m;
  char *load_file;


  auto start = chrono::high_resolution_clock::now();


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
  init_tree(&t, &i);
  init_manager(&m, &t, &i);
  // execute_work(&m, &t, &i);


  print_tree(&t);

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "time: " << duration.count() << " milliseconds" << endl;
}
