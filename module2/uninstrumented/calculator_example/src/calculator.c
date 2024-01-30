#include <stdio.h>
#include <assert.h>

int add(int x, int y) {
  return x + y;
}

int subtract(int x, int y) {
  return x - y;
}

int multiply(int x, int y) {
  return x * y;
}

int divide(int x, int y) {
  if(y == 0) 
    return 0;
  return x / y;
}

int factor_game(int x, int y) {
  if(multiply(x,y) == 100){
    printf("You win! Here is your bug!\n");
    assert(0);
  }
  return 0;
}
