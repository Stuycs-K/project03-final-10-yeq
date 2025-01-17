#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define KEY 24601

//group id 40


//take a step size
int escape(long double x, long double y){
  long double nX = x;
  long double nY = y;
  int i = 0;
  while(i < 500){
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
  // char *data[4];
  // int shmid;
  // shmid = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
  // printf("shmid: %d\n", shmid);
  // data = shmat(shmid, 0, 0);
  // char * head[4] = data;


  // int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  long double x = -2.0; long double y = -1.5;
  // int pixels = 900;
  int pixels = 2000;
  int n = -2;
  char buff[32] = "";
  sprintf(buff, "P3 %d %d 255\n", pixels, pixels);
  // sprintf(buff, "P1 %d %d\n", pixels, pixels);
  write(fd, buff, sizeof(buff));
  //number of children
  //use that index in a loop to give segments and memory address.
  int num_child = 1;
  pid_t p = -1;
  double start = 0.0;
  double end = 0.0;
  double temp = pixels;
  int id = -1;
  for (int i = 1; i <= num_child; i++){
    if (p){
      end = i * temp/num_child;
      id = i - 1;
      // data =  data + ((end - start) * 3);
      p = fork();
    }
    start = end - temp/num_child;
  }
  if (p != 0){
    id = -1;
    start = -1;
    end = -1;
  }
  printf("%d\n", id);
  printf("start: %f\n", start);
  printf("end: %f\n", end);
  if (p == 0){
    // printf("%d\n", id);
    // printf("%f %f\n", start, end);
    char f[10];
    sprintf(f, "%d.ppm", id);
    fd = open(f, O_WRONLY| O_TRUNC | O_CREAT, 0644);
    int a = end - start;
    // printf("%d\n", a);

    // sprintf(buff, "P3 %d %d 255\n", pixels, a);
    // write(fd, buff, sizeof(buff));

    y += (3.0/pixels) * start;
    // printf("%Lf\n", y);
    for (int i = start; i < end; i++){
      // y += 3.0/pixels;
      // printf("%Lf\n", y);
      // y = -1.5 + i * 3.0/pixels;
      y += 3.0/pixels;
      x = -2.0;
      for (int j = 0; j < pixels; j++){
        if (i == end - 1 && j == pixels - 1 && id == num_child - 1){
          // printf("%d, %d\n", i, j);
          break;
        }
        x += 3.0/pixels;
        if ((n = escape(x, y)) >= 0){
          write(fd, "255 255 255 ", 12);
          // write(fd, "1 ", 3);
          // write(fd, "1", 2);
        }
        else{
          // write(fd, "0", 2);
          // write(fd, "0 ", 3);
          // write(fd, "0 0 0 ", 7);
          write(fd, "000 000 000 ", 12);
        }
      }
    }
    if (id == num_child - 1){
      y += 3.0/pixels;
      if ((n = escape(x, y)) >= 0){
        write(fd, "255 255 255", 11);
        // write(fd, "1", 2);
      }
      else{
        // write(fd, "0", 2);
        write(fd, "000 000 000", 11);
      }
    }
  }
  else{
    while(wait(NULL) > 0);
    printf("combining...\n");
    char f[16];

    int tempfd = -1;
    // struct stat * stat_buffer;
    // char * buff;
    // char * p;
    // char tmp[2];
    char tmp[13] = "";
    for (int i = 0; i < num_child; i++){
      printf("%d\n", i);
      sprintf(f, "%d.ppm", i);
      // stat(f, stat_buffer);
      tempfd = open(f, O_RDONLY);
      // printf("%d\n", i);
      while(read(tempfd, tmp, 12)){
        // write(fd, tmp, 1);
        // write(fd, " ", 1);
        write(fd, tmp, 12);
      }
    }
    printf("done\n");
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
