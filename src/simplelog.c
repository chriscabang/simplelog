#undef DEBUG
#define DEBUG

#include "simplelog.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void log_printf(int level, const char *fmt, ...) {
  if (level > 0) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
  }
}