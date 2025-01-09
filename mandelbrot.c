#include <stdio.h>
#include <stdlib.h>

int escape(int x, int y){
  int n = 0;
  int nX = x;
  int nY = y
  int i = 0;
  while(i < 1000){
    if (abs(x) > 2 or abs(y) > 2){
      return n;
    }
    int tempX = (x * x) + (y * y * -1) + nX;
    y = 2 * x * y + nY;
    x = tempX;
    n += 1;
    i++;
  }
  return -1;
}
