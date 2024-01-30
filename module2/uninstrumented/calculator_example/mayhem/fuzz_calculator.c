#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "calculator.h"

// Let's turn it up a notch with some Mayhem! 
// We'll test:
//    * Basic algebra works as expected.
//    * We don't get runtime errors.

// test x + y = y + x
void test_add_commutes(int x, int y) {
   assert(add(x,y) == add(y,x));
}

// test x + y - y = x
void test_add_subtract(int x, int y) { 
   assert(subtract(add(x,y),y) == x);
}

// test x * y = y * x
void test_multiply_commutes(int x, int y) {
   assert(multiply(x,y) == multiply(y,x));
}

// test (x * x) / x =  x
//
// Mayhem finds a subtle vulnerability easily missed manually.
// Details: When x*x overflows, the result is negative.
//          dividing by x is still negative, thus
//          violating the assertion.  
//         example: x = 87570
void test_cancel_divisor(int x) {
  int product = multiply(x,x);
  assert(divide(product, x) == x);
}


// Mayhem can even solve puzzles like the factor game!
void test_factor_game(int x, int y) {
  assert(factor_game(x,y) == 0);
}

int main(int argc, char *argv[]) {
  int x, y;
  
  if(scanf("%d%d", &x, &y) != 2){
    printf("Invalid input\n");
    return 0;
  }

  test_add_commutes(x,y);
  test_add_subtract(x,y);
  test_multiply_commutes(x,y);
  test_cancel_divisor(x);
  test_factor_game(x,y);
  return 1;
}
