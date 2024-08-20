#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc.h"

int main(int argc,char **argv){
  struct proc *p = myproc();
  p->state = 2;
  return 0;
}
