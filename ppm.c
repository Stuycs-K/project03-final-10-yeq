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

int main(){
  int fd = open("render.ppm", O_WRONLY| O_TRUNC | O_CREAT, 0644);
  long double x = -2.0; long double y = -1.5;
  // int pixels = 900;
  int pixels = 9;
  int n = -2;
  char buff[32] = "";
  sprintf(buff, "P3 %d %d 255\n", pixels, pixels);
  write(fd, buff, sizeof(buff));
  //number of children
  //use that index in a loop to give segments and memory address.
  int num_child = 9;
  pid_t p = -1;
  double start = 0.0;
  double end = 0.0;
  double temp = pixels;

  printf("combining...\n");
  char f[16];

  // char buff[1024] = "";
  int tempfd = -1;
  // struct stat * stat_buffer;
  // char * buff;
  // char * b;
  char b[1092];
  for (int i = 0; i < 9; i++){
    printf("%d\n", i);
  //stat to read size of file
    sprintf(f, "%d.ppm", i);
    // stat(f, stat_buffer);
    // b = calloc((100), sizeof(char));
    tempfd = open(f, O_RDONLY);
    while(read(tempfd, b, 1092)){
      printf("%s\n", b);
      write(fd, b, 1092);
      // stat_buffer->st_size
    }
    // free(b);
  }
  printf("done\n");
}
