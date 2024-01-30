#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "calculator.h"

// Simple unit test:
//   "with this specific input, we expect this specific output"

void test_add() {
  assert(add(1, 2) == 3);
}

void test_subtract() {
  assert(subtract(2, 1) == 1);
}

void test_multiply() {
  assert(multiply(3, 2) == 6);
}

int main() {
  test_add();
  test_subtract();
  test_multiply();
  return 0;
}
