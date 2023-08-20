/**
 * FILENAME : simplelog.c
 * 
 * The MIT License (MIT)
 *
 * Copyright (c) 2023-2026 Chris Cabang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#undef  DEBUG
#define DEBUG

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "simplelog.h"

const char* log_levels[] = {
  "LOG_INFO", 
  "LOG_DEBUG", 
  "LOG_WARN",
  "LOG_ERROR"
};

void log_printf(int level, const char* file, int line, const char* fn, const char *fmt, ...) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  time_t t = tv.tv_sec;
  struct tm tm_info = *localtime(&t);

  va_list args;
  va_start(args, fmt);
  
  fprintf(stderr, "[    %02d:%02d:%02d.%03d] %-10s %s:%s():%-6d : ", 
    tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec, tv.tv_usec/1000, 
    log_levels[level],
    file, fn, line);
  vfprintf(stderr, fmt, args);

  va_end(args);
}