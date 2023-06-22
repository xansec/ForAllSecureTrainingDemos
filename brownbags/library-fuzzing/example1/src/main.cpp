#include <string.h>
#include "MyCustomCxxLib.h"
#include "my_custom_c_lib.h"

int main(int argc, char *argv[]) {
  for(int a = 1; a < argc; a++) {
    // Pretend that 'in' comes from somewhere difficult. Lets say that
    // it comes from a serial device, taking in sensor readings.
    const char *in = argv[a];

    char *out = new char[strlen(in)+5];
    int x = MyCustomCxxLib::process_data(in, out);
    my_custom_c_lib_process_data(out, x);

    if(strcmp(in, "magic") == 0) {
      // Note that if this program had some kind of crash here,
      // harnessing the "process_data" functions won't find it.
      // Harnessing libraries is harnessing a subset of the application,
      // and inherently misses non-library code.
      // ...except in this simple example, there's no real code here :P
    }

    delete[] out;
  }

  return 0;
}
