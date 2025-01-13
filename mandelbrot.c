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

//take a step size
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


//forks write into a file called their fork number and is read and written into an original file.
//shared mem
//write into a specific area and piece it together to write into a file.
//for a user input of amount of processes, the program should (Set an upper limit) and set a memory address in shared mem by
//using index of loop
//split into that many rows

//doesnt use any optimizations like reflecting the logistic map across its center axis
int main(){
  int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  long double x = -2.0; long double y = -1.5;
  int pixels = 900;
  int n = -2;
  char buff[18];
  sprintf(buff, "P3 %d %d 255\n", pixels, pixels);
  write(fd, buff, sizeof(buff));
  //number of children
  //use that index in a loop to give segments and memory address.
  int num_child = 4;
  pid_t p = -1;
  double start = 0.0;
  double end = 0.0;
  double temp = pixels;
  int id = -1;
  for (int i = 1; i <= num_child; i++){
    if (p){
      end = i * temp/num_child;
      id = i - 1;
      p = fork();
    }
    start = end - temp/num_child;
  }
  if (p != 0){
    id = -1;
    start = -1;
    end = -1;
  }
  // printf("%d\n", id);
  // printf("start: %f\n", start);
  // printf("end: %f\n", end);
  if (p == 0){
    printf("%d\n", id);
    printf("%f %f\n", start, end);
    char f[10];
    sprintf(f, "%d.ppm", id);
    fd = open(f, O_WRONLY| O_TRUNC | O_CREAT, 0644);
    int a = end - start;
    printf("%d\n", a);
    sprintf(buff, "P3 %d %d 255\n", a, a);
    write(fd, buff, sizeof(buff));
    for (int i = start; i < end; i++){
      y = i * 3.0/pixels;
      x = -2;
      for (int j = 0; j < pixels; j++){
        if (i == end - 1 && j == pixels - 1){
          printf("%d, %d\n", i, j);
          break;
        }
        x += 3.0/pixels;
        if ((n = escape(x, y)) >= 0){
          write(fd, "255 255 255 ", 13);
        }
        else{
          write(fd, "0 0 0 ", 7);
        }
      }
    }
    y += 3.0/pixels;
    if ((n = escape(x, y)) >= 0){
      write(fd, "255 255 255", 12);
    }
    else{
      write(fd, "0 0 0", 6);
    }
  }
}



//original working code

// for (int i = 0; i < pixels; i++){
//   y += 3.0/pixels;
//   x = -2;
//   for (int j = 0; j < pixels; j++){
//     if (i == pixels - 1 && j == pixels - 1){
//       break;
//     }
//     x += 3.0/pixels;
//     if ((n = escape(x, y)) >= 0){
//       write(fd, "255 255 255 ", 13);
//     }
//     else{
//       write(fd, "0 0 0 ", 7);
//     }
//   }
// }
// y += 3.0/pixels;
// if ((n = escape(x, y)) >= 0){
//   write(fd, "255 255 255", 12);
// }
// else{
//   write(fd, "0 0 0", 6);
// }

//


//forking
//function that takes an area input, divides it into some square? amount of areas and forks to calculate each area
//each fork has a number associated to input data in order (prob rows then)
