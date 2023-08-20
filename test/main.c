#include <stdio.h>

#include <simplelog.h>

int main() {
  printf("Hello World\n");

  log_info("this is info\n");
  log_debug("and this prints debug\n");
  log_error("while this logs error\n");
  log_warn("and this a warning\n");

  return 0;
}