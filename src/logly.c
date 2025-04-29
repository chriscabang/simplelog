/**
 * FILENAME : logly.c
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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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

#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logly.h"

FILE *log_stream = NULL;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

void log_set_stream(FILE *stream) {
  log_stream = (stream != NULL) ? stream : stderr;
}

void log_write(const char *level, const char *file, const char *func, int line,
               const char *fmt, ...) {
  struct timespec ts;
  struct tm tm_info;
  char log_buffer[LOG_BUFFER_SIZE];
  char timestamp[32] = "";
  va_list args;

  pthread_mutex_lock(&log_mutex);

  if (log_stream == NULL) {
    log_stream = stderr;
  }

  clock_gettime(CLOCK_REALTIME, &ts);
  localtime_r(&ts.tv_sec, &tm_info);

  // Format the timestamp
  snprintf(timestamp, sizeof(timestamp),
           "[%04d-%02d-%02d %02d:%02d:%02d.%03ld] ", tm_info.tm_year + 1900,
           tm_info.tm_mon + 1, tm_info.tm_mday, tm_info.tm_hour, tm_info.tm_min,
           tm_info.tm_sec, ts.tv_nsec / 1000000);

  // Format source and function information
  int source_info_len = strlen(file) + strlen(func);
  char *source_info = malloc(source_info_len + 1);
  snprintf(source_info, source_info_len + 2, "%s:%s", file, func);

  // Format the log message
  va_start(args, fmt);
  int log_len =
      snprintf(log_buffer, sizeof(log_buffer),
               "%s%-5s %-32s @ Ln.%d: ", timestamp, level, source_info, line);
  vsnprintf(log_buffer + log_len, sizeof(log_buffer) - log_len, fmt, args);
  va_end(args);

  // Write the log message to the log stream
  fprintf(log_stream, "%s", log_buffer);
  fflush(log_stream);

  // Clean up
  free(source_info);
  source_info = NULL;

  pthread_mutex_unlock(&log_mutex);
}
