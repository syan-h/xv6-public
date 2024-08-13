#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

int 
sys_addnums(void){

  int a,b;
  if (argint(0, &a) < 0)
    return -1;
  if (argint(1, &b) < 0)
    return -1;
  return a+b;

}



int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

extern struct {
	struct spinlock lock;
	struct proc proc[NPROC];
   
} ptable;


int 
sys_prog(void){
   
  struct proc *p;
  
  for(p = ptable.proc; p < &ptable.proc[NPROC];p++){
    if(p->state == 4){
      cprintf("PID = %d NAME = %s",p->pid,p->name);	
      cprintf("\n");
    }
    else{
      continue;
    }

  }
  
  return 0;
	
}




















