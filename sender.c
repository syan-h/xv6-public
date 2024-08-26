#include "types.h"
#include "stat.h"
#include "user.h"





int main(int argc,char **argv) {
  const int MAX_PID = 5;
  int pid[MAX_PID];
  
  int i;
  for (i=0;i<atoi(argv[1]);i++){
	pid[i] = atoi(argv[2+i]);
  }
  
  char *message = argv[ atoi(argv[1]) + 2 ] ;
  
  send_message(pid,message);
 
  exit();
}
