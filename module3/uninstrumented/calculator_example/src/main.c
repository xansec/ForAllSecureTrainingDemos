#include <stdio.h>
#include "calculator.h"

int main(int argc, char *argv[]) {
  int x, y;
  char op;
  x = y = op = 0;

  // Read in <op> <x> <y>, where <op> = +, -, *, /, or g for game.
  if(scanf("%c%d%d", &op, &x, &y) != 3){
    printf("Invalid input\n");
    return 0;
  }

  switch(op){
    case '+': printf("%d + %d = %d\n", x, y, add(x,y)); break;
    case '-': printf("%d - %d = %d\n", x, y, subtract(x,y)); break;
    case '*': printf("%d * %d = %d\n", x, y, multiply(x,y)); break;
    case '/': printf("%d * %d = %d\n", x, y, divide(x,y)); break;
    case 'g': 
      printf("%s\n", factor_game(x,y) == 1 ? "Win!" : "Lose\n"); 
      break;
    default: printf("%c not supported\n", op);
  }
  return 0;
}
