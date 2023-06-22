#include <string.h>
#include <iostream>
#include <ex2lib.hxx>

int main(int argc, char *argv[]) {
  if(argc < 2) {
    std::cerr << "need an arg" << std::endl;
    return -1;
  }

  // Harnessing note: It's somewhat typical for real programs not to function
  // unless runtime setup of certain global variables occurs. Sometimes this
  // must be done manually; but usually, there will be a function that does
  // this (like this one here).
  initialization_func();

  // Reverse engineering note: to determine the size of CustomClassA, just
  // find a 'new CustomClassA()'. In C++, this compiles down to a call to
  // "operator new(sizeof CustomClassA)" (revealing the size of the class)
  // and a call to an initializer.
  // For classes that are only constructed on the stack (unlike here), you
  // can usually get the size by checking the class constructors for the
  // highest member field that is set by the constructor.
  CustomClassA *a = new CustomClassA();

  std::map<int, std::string> m;
  m[1338] = "foo";
  m[1339] = "bar";
  m[1340] = "baz";

  CustomClassB *b = new CustomClassB(a, m);

  return b->harness_me(argv[1], strlen(argv[1]));
}
