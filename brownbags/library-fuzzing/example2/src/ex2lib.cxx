#include <iostream>
#include <stdlib.h>

#include "ex2lib.hxx"

std::vector<std::string> globalObject;
static int globalCounter = 0;

void initialization_func() {
  static bool initialized = false;
  if(initialized)
    return;
  initialized = true;
  globalObject = std::vector<std::string>(10, std::string("empty"));
}

void debug_warn_about(const char *name) {
  std::cerr << "Looks like " << name << " wasn't initialized properly." << std::endl;
  std::cerr << "This program will crash spuriously or behave incorrectly." << std::endl;
  std::cerr << "A real program wouldn't have given you any warning!" << std::endl;
}

CustomClassA::CustomClassA() : magic(0xdeadbeef) {
  member.push_back(1337);
}

CustomClassA::~CustomClassA() {}

int *CustomClassA::methodA() {
  return &member[0];
}

CustomClassB::CustomClassB(CustomClassA *arg1, std::map<int, std::string> &arg2) : a(arg1), m(&arg2), magic(0xfeedface) {
  if(!a || a->magic != 0xdeadbeef) {
    debug_warn_about("that CustomClassA instance");
  }
  int start = *a->methodA();
  (*m)[start] = "start";
}

std::string CustomClassB::methodB() {
  int *x = a->methodA();
  std::string &ret = (*m)[*x];
  if(ret == "") {
    if(globalCounter >= globalObject.size()) {
      std::cerr << "(congratz, you're hitting the bug)" << std::endl << std::flush;
    }
    ret = globalObject[globalCounter] = (const char*)"abcd" + (*x % 3);
    globalCounter += 1;
  }
  *x += 1;
  return ret;
}

int CustomClassB::harness_me(char *data, int len) {
  if(globalObject.size() != 10) {
    debug_warn_about("the globalObject");
  }
  if(magic != 0xfeedface) {
    debug_warn_about("this CustomClassB instance");
  }
  std::cerr << "running" << std::endl;
  for(int i = 0; i < len; ++i) {
    if(data[i] == ('A' ^ i)) {
      std::cout << methodB() << std::endl;
    }
  }
  return 0;
}
