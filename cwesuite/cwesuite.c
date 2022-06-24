#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define BLOCK_SIZE 256

/***
#define BASIC
#define ADVANCED
#define SANITIZE
***/

int triggerCWEs(char *buf, unsigned len);
char* getBlock(int fd);

int main(int argc, char *argv[])
{
  FILE *f;
  char buf[20];

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
  triggerCWEs(buf, strlen(buf));
  return 0;
}

char* getBlock(int fd) {
  char* buf = (char*) malloc(BLOCK_SIZE);
  if (!buf) {
    return NULL;
  }
  if (read(fd, buf, BLOCK_SIZE) != BLOCK_SIZE) {

    return NULL;
  }
  return buf;
}

int triggerCWEs(char *buf, unsigned len)
{
  unsigned var;
  char *p;
  int *arr = (int *)malloc(len * sizeof(int));

  switch(buf[0]) {

    #ifdef BASIC
    #ifdef CWE20
    //CWE-20: Improper Input Validation
    case 0 :
      p = &buf[0]; // Defect: allocating and then freeing memory incorrectly from user input
      free(p);
      break;
    #endif

    #ifdef CWE121
    //CWE-121: Stack-Based Buffer Overflow
    case 1 :
      arr[buf[len - 1]] = buf[len - 2]; //Defect: input might overflow (see also 913)
      break;
    #endif

    #ifdef CWE125b
    //CWE-125: Out-of-Bounds read
    case 2 :
      var = buf[1 - len]; // Defect: incorrectly using address of buffer to read a value
      break;
    #endif

    #ifdef CWE369
    //CWE-369: Divide By Zero
    case 3 :
      var = 1/0;      // Defect: divide-by-zero.
      break;
    #endif

    #ifdef CWE476
    //CWE-476: NULL Pointer Dereference
    case 4 :
      var = *p; // Defect: pointer p is not allocated
      break;
    #endif

    #ifdef CWE763
    //CWE-763: Release of Invalid Pointer or Reference
    case 5 :
      //memcpy(arr, buf, sizeof(arr));
      //free(arr[len]); //Could not get this one to fire
      break;
    #endif

    #ifdef CWE787b
    //CWE-787: Out-of-bounds Write
    case 6 :
      buf[1 - len] = 'c'; //Defect: writing a character past the length of the buffer
      break;
    #endif

    #ifdef CWE913b
    //CWE-913: Improper Control of Dynamically-Managed Code Resources
    case 7 :
      arr[buf[len - 1]] = buf[len - 2]; //Defect: input might overflow and point to a malicious function
      break;
    #endif
    #endif

    /*************************************************************************/

    //Advanced Triage

    #ifdef ADVANCED
    #ifdef CWE119
    //CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
    case 8 :
      printf("Your array item is %s\n", arr[buf[len - 1]]); //Defect: no checking of buffer value to see if it overflows arr[]
      break;
    #endif

    #ifdef CWE125a
    //CWE-125: Out-of-Bounds read
    case 9 :
      var = buf[len + 1]; // Defect: reading past the length of the buffer
      break;
    #endif

    #ifdef CWE131
    //CWE-131: Incorrect Calculation of Buffer Size
    case 10 :
      for(int i; i < len; i++) {
        arr[i] = buf[i];
      }
      arr[len] = NULL;
      break;
    #endif

    #ifdef CWE401
    //CWE-401: Missing Release of Memory after Effective Lifetime
    case 11 :
      p = getBlock(10);
      break;
    #endif

    #ifdef CWE457
    //CWE-457: Use of Uninitialized Variable
    case 12 :
      var = len;
      break;
    #endif

    #ifdef CWE590
    //CWE-590: Free of Memory not on the Heap
    case 13 :
      free(arr);
      break;
    #endif

    #ifdef CWE704
    //CWE-704: Incorrect Type Conversion or Cast
    case 14 :
      var = (unsigned)buf;
      break;
    #endif

    #ifdef CWE787a
    //CWE-787: Out-of-bounds Write
    case 15 :
      buf[len + 1] = 'c'; //Defect: writing a character past the length of the buffer
      break;
    #endif

    #ifdef CWE913a
    //CWE-913: Improper Control of Dynamically-Managed Code Resources
    case 16 :
      arr[buf[len - 1]] = buf[len - 2]; //Defect: input might overflow and point to a malicious function
      break;
   #endif
   #endif

    /*************************************************************************/

    //Sanitizer


   #ifdef SANITIZE
     // code
   #endif


  }

  return 0;
}
