#include <vector>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

class CustomClassA {
  std::vector<int> member;
public:
  unsigned magic;

  CustomClassA();
  ~CustomClassA();
  int *methodA();
};

class CustomClassB {
  CustomClassA *a;
  std::map<int, std::string> *m;
public:
  unsigned magic;

  CustomClassB(CustomClassA *arg1, std::map<int, std::string> &arg2);
  std::string methodB();

  int harness_me(char *data, int len);
};

extern std::vector<std::string> globalObject;
extern void initialization_func();
