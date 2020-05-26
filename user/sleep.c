#include "kernel/types.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char** argv){
  if(argc < 2){
    fprintf(2, "failure: missing: specify time in seconds\n");
    exit(1);
  }
  int x = atoi(argv[1]);
  sleep(x);
  exit(0);
}