#include "types.h"
#include "stat.h"
#include "user.h"





int main(int argc,char **argv) {
  char *message = argv[1];
  send_message(message);
  
  exit();
}
