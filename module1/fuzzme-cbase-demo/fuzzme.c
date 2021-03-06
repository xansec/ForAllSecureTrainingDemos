#include <stdio.h>
#include <string.h>

int fuzzme(char *buf)
{
  if(strlen(buf) >= 3)
    if(buf[0] == 'b')
      if(buf[1] == 'u')
        if(buf[2] == 'g') {
          printf("You've got it!");
	  return 1/0;      // Defect: divide-by-zero.
        }
  return 0;
}

void dontcallme()
{
  int two = 2;
  int four = two + two;
  if(four == 4) {
    printf("Great!");
  }
  return;
}

int main(int argc, char *argv[])
{
  FILE *f;
  char buf[12];
  
  if(argc != 2){
    fprintf(stderr, "Must supply a text file\n");
    return -1;
  }
  f = fopen(argv[1], "r");
  if(f == NULL){
    fprintf(stderr, "Could not open %s\n", argv[1]);
    return -1;
  }
  if(fgets(buf, sizeof(buf), f) == NULL){
    fprintf(stderr, "Could not read from %s\n", argv[1]);
    return -1;
  }
  fuzzme(buf);
  return 0;
}
