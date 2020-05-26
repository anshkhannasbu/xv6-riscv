#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char** argv){
  int n = 0;
  char *argval[MAXARG], curarg[512], c;
  char* curargptr = curarg;

  while(argv[n+1]){
    argval[n] = (char*)malloc(sizeof(char)*strlen(argv[n+1]));
    strcpy(argval[n], argv[n+1]);
    n++;
  }
  int xtrarg_cnt = n;
  while(read(0, &c, 1) > 0){
    if(c == '\n'){
      *curargptr = 0;
      argval[xtrarg_cnt] = (char*)malloc(sizeof(char)*strlen(curarg));
      strcpy(argval[xtrarg_cnt], curarg);
      xtrarg_cnt++;
      curargptr = curarg;
      *curargptr = 0;

      if(fork() == 0){
        exec(argval[0], argval);
      }else{
        wait(0);
        while(xtrarg_cnt > n){
          free(argval[xtrarg_cnt-1]);
          xtrarg_cnt--;
        }
      }
    }else if(c == ' '){
      *curargptr = 0;
      argval[xtrarg_cnt] = (char*)malloc(sizeof(char)*strlen(curarg));
      strcpy(argval[xtrarg_cnt], curarg);
      xtrarg_cnt++;
      curargptr = curarg;
      *curargptr = 0;
    } else{
      *curargptr = c;
      curargptr++;
    }
  }
  exit(0);
}