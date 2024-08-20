#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  char message[128];
  recieve_message(message);
  printf(1, "Received message: %s\n", message);
  exit();
}
