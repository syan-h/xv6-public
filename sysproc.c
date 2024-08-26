#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"


struct message{
  int sender_pid;
  int reciever_pid[5];
  char msg[128];

};

struct message msg_buffer;
struct spinlock msg_lock;

void init_msglock(void){
  initlock(&msg_lock,"msg_lock");

}



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
      if (p->pid != 0){
	      cprintf("PID = %d NAME = %s",p->pid,p->name);	
       	      cprintf("\n");
       	  
         
	
       }
  }
  
  return 0;
	
}


int pid_check(int pid,int *pointer){

  int i;
  for(i=0;i<5;i++){
    
    if(pid == pointer[i]){
      return 1;
    }
  }
  return 0;


}


int sys_send_message(void){
  
  int (*reciever_pid);
  char *msg;
  
  if (argptr(0,(void*)&reciever_pid,5 * sizeof(int)) < 0 || argstr(1,&msg) < 0)
	return -1;
  

  acquire(&msg_lock);
  
  int i;
  for(i=0;i<5;i++){
    msg_buffer.reciever_pid[i] = reciever_pid[i];
  
  }
  msg_buffer.sender_pid = myproc()->pid;
  safestrcpy(msg_buffer.msg,msg,sizeof(msg_buffer.msg));
  
  release(&msg_lock);
  
  return 0;



}



int sys_recieve_message(void){
  char *msg;

   cprintf("PID = %d\n",myproc()->pid);   
   if (argstr(0, &msg) < 0)
     return -1;


    acquire(&msg_lock);
    if ( pid_check(myproc()->pid,msg_buffer.reciever_pid) ) {
       
	safestrcpy(msg, msg_buffer.msg, sizeof(msg_buffer.msg));
       release(&msg_lock);
       return 0;
    }
  
  release(&msg_lock);
  return -1;
}




