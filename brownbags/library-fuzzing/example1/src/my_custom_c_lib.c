#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void my_custom_c_lib_process_data(char *buf, int len) {
  // Pretend like this is interesing and meaningful processing.
  // Maybe say we're formatting the buffer data into a human-readable
  // format, and storing it somewhere.

  // Stand-in for something that causes this function to only work properly
  // if it's operating on the output of MyCustomCxxLib::process_data()
  if(strncmp("xyzzy", buf, 5) != 0) {
    fputs("bad format!\n", stderr);
    abort();
  }

  // Stand-in for some kind of real bug :P
  if(len > 40 && buf[5] == 'C' && buf[15] == 'R' && buf[25] == 'A'
     && buf[35] == 'S' && buf[45] == 'H')
  {
    fputs("you found the crash!\n", stderr);
    fflush(stderr);
    **(int**)&buf[1] = *(int*)&buf[11];
  }

  for(int i = len-1; i >= 0; i--)
    putchar(buf[i+5] ^ ((len - i - 1) % 7));
  putchar('\n');
}
