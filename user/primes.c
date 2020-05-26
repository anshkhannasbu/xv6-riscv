#include "kernel/types.h"
#include "user/user.h"

void init_pipeline(int fd){
  int pr, fdn[2], status = 0;

  rec:

  if(pipe(fdn) < 0){
    exit(1);
  }
  if(read(fd, &pr, 4) != 4){
    exit(1);
  }
  printf("prime %d\n", pr);
  if(fork() == 0){
    close(fd);
    close(fdn[1]);
    fd = fdn[0];
    goto rec;
  }

  close(fdn[0]);

  while(1){
    int x;
    if(read(fd, &x, 4) != 4){
      close(fdn[1]);
      wait(&status);
      exit(1);
    }
    if(x%pr){
      write(fdn[1], &x, 4);
    }
  }
}

void
primes(){
  int p[2], fork_stat, pipe_stat, status = 0;
  pipe_stat = pipe(p);
  if(pipe_stat < 0){
    exit(1);
  }
  fork_stat = fork();
  if(fork_stat < 0){
    exit(1);
  }
  if(fork_stat == 0){
    close(p[1]);
    init_pipeline(p[0]);
  }else{
    close(p[0]);
    for(int i = 2; i <= 35; i++){
      if(write(p[1], &i, 4) != 4){
        exit(1);
      }
    }
    close(p[1]);
    wait(&status);
  }
}

int
main(int argc, char **argv){
  primes();
  exit(0);
}