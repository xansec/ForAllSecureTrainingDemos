#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  putenv("MYVAR=\"hahaha\"");
  printf(getenv("MYVAR"));
  return 0;
}
