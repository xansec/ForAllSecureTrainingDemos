//
// Compile with: c++ -o harness harness.cxx MyCustomCxxLib.so my_custom_c_lib.so
//

#include <stdio.h>
#include <string.h>

namespace MyCustomCxxLib {
  int process_data(const char*, char*);
}

// In C++, C functions must be declared with extern "C".
// This lets C++ know to look for the unmangled name when linking.
extern "C" void my_custom_c_lib_process_data(char*, int);


// Helper function for reading in a fuzzing testcase file.
char *read_whole_file(const char *filepath) {
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

  return buf;
}

int main(int argc, char *argv[]) {
  const char *filepath = argc >= 2 ? argv[1] : "/no/path/provided";
  char *buf = read_whole_file(filepath);
  if(!buf)
    return 1;
  
  char *out = new char[strlen(buf)+5];
  int x = MyCustomCxxLib::process_data(buf, out);
  my_custom_c_lib_process_data(out, x);

  //delete[] buf;
  //delete[] out;
  return 0;
}
