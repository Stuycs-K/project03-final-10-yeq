#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

// struct pixel {
//   int x;
//   int y;
//   int color;
// };
//
// int escape(int x, int y){
//   int n = 0;
//   int nX = x;
//   int nY = y
//   int i = 0;
//   while(i < 1000){
//     if (abs(x) > 2 or abs(y) > 2){
//       return n;
//     }
//     int tempX = (x * x) + (y * y * -1) + nX;
//     y = 2 * x * y + nY;
//     x = tempX;
//     n += 1;
//     i++;
//   }
//   return -1;
// }

int main(){
  // malloc(900 * sizeof(pizel));
  int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  write(fd, "P3 900 900 255", 16);

}
