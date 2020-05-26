#include "kernel/types.h"
#include "user/user.h"

void
pingpong(){
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  if(fork() == 0){
    write(p2[1], "a", 1);
    char byte;
    int pid = getpid();
    while(1) {
      if(read(p1[0], &byte, 1) < 0){
        close(p1[0]);
        close(p2[1]);
        break;
      }
      printf("%d: received ping\n", pid);
      write(p2[1], &byte, 1);
    }
  } else{
    int pid = getpid();
    int x = 0;
    char byte;
    while(1) {
      read(p2[0], &byte, 1);
      printf("%d: received pong\n", pid);
      write(p1[1], &byte, 1);
      x++;
      if(x == 100){
        close(p1[1]);
        close(p2[0]);
        break;
      }
    }
  }
}

int
main(int argc, char** argv){
  pingpong();
  exit(0);
}