//
// Compile with g++ -std=gnu++03 -D_GLIBCXX_USE_CXX11_ABI=0 harness.cxx ex2lib.so -o harness
//

#include <string.h>
#include <stdio.h>
#include <map>
#include <string>

class CustomClassA {
  char space[40]; // Note: 40 depends on the physical size of std::vector,
                  // which changes between platforms and compilers!
public:
  CustomClassA();
  virtual ~CustomClassA();
  virtual int *methodA();
};

class CustomClassB {
  char space[24];
public:
  CustomClassB(CustomClassA*, std::map<int, std::string> &);
  int harness_me(char*, int);
};


void initialization_func();

// Helper function for reading in a fuzzing testcase file.
char *read_whole_file(const char *filepath, int *bytes_read) {
  FILE *f = fopen(filepath, "rb");
  if(!f) {
    fprintf(stderr, "error opening %s\n", filepath);
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *buf = new char[size+1];
  if(fread(buf, size, 1, f) != 1) {
    fprintf(stderr, "error reading %s\n", filepath);
    return NULL;
  }
  buf[size] = 0;
  if(bytes_read)
    *bytes_read = size;

  return buf;
}

int main(int argc, char *argv[]) {
  const char *filepath = argc >= 2 ? argv[1] : "/no/path/provided";
  int size;
  char *buf = read_whole_file(filepath, &size);
  if(!buf)
    return 1;

  initialization_func();
  CustomClassA a;
  std::map<int, std::string> m;
  CustomClassB b(&a, m);
  return b.harness_me(buf, size);
}
