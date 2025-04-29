/**
 * FILENAME : logly.h
 * AUTHOR   : Chris Cabang
 * DATE     : August 20, 2023
 * 
 * DESCRIPTION :
 *       Simple logging mechanism for C projects. 
 *
 * PUBLIC FUNCTIONS :
 *       void   log_info(...)
 *       void   log_debug(...)
 *       void   log_warn(...)
 *       void   log_error(...)
 * 
 * LICENSE :
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

#ifndef __LOGLY_H__
#define __LOGLY_H__

#undef ENABLED
#if defined(DEBUG)
  #define ENABLED 1
#else
  #define ENABLED 0
#endif

#include <stdio.h>
#include <string.h>

#define LOG_INFO "INFO"
#define LOG_WARN "WARN"
#define LOG_ERROR "ERROR"
#define LOG_DEBUG "DEBUG"

#define LOG_BUFFER_SIZE 512

extern FILE* log_stream;

void log_set_stream(FILE *stream);
void log_write(const char *level, const char *file, const char *func, int line,
               const char *fmt, ...);

#if defined (__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

#define log_info(fmt, ...) \
  log_write(LOG_INFO, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...) \
  log_write(LOG_WARN, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) \
  log_write(LOG_ERROR, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define log_debug(fmt, ...) \
  log_write(LOG_DEBUG, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)


#if defined (__clang__)
#pragma clang diagnostic pop
#endif
#endif//__LOGLY_H__ 
