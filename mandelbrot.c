#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <math.h>

// struct pixel {
//   int x;
//   int y;
//   int color;
// };
//
int escape(long double x, long double y){
  long double nX = x;
  long double nY = y;
  int i = 0;
  while(i < 2500){
    // if (fabs(x) > 2 || fabs(y) > 2){
    //   return i;
    // }
    if ((x * x + y * y) > 4) {
    return i;
}
    i+=1;
    long double tempX = (x * x) + (y * y * -1) + nX;
    // printf("%Lf\n", tempX);
    y = 2 * x * y + nY;
    x = tempX;
    // printf("x: %Lf\n", x);
    // printf("y: %Lf\n", y);
    // printf("i: %d\n", i);

  }
  return -1;
}

int main(){
  // malloc(900 * sizeof(pizel));
  int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  // write(fd, "P3 900 900 255\n", 16);
  // write(fd, "P3 1 1 255\n", 12);
  // write(fd, "255 255 255\n", 12);
  // escape(-0.123,0.745);
  // int a = escape(-0.74543,0.11301);
  // int a = escape(-0.85,0);
  // printf("%d\n", a);
  long double x = -2.0; long double y = -1.5;
  int pixels = 900;
  int n = -2;
  char buff[18];
  sprintf(buff, "P3 %d %d 255\n", pixels, pixels);
  write(fd, buff, sizeof(buff));
  for (int i = 0; i < pixels; i++){
    y += 3.0/pixels;
    x = -2;
    // printf("%Lf\n", x);
    for (int j = 0; j < pixels; j++){
      if (i == pixels - 1 && j == pixels - 1){
        break;
      }
       x += 3.0/pixels;
       if ((n = escape(x, y)) >= 0){
         // printf("%d\n", n);
         write(fd, "255 255 255 ", 13);
       }
       else{
         // printf("%d\n", n);
         write(fd, "0 0 0 ", 7);
       }
    }
  }
  y += 3.0/pixels;
  if ((n = escape(x, y)) >= 0){
    // printf("%d\n", n);
    write(fd, "255 255 255", 12);
  }
  else{
    // printf("%d\n", n);
    write(fd, "0 0 0", 6);
  }
}
