/**
 * FILENAME : simplelog.h
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
#ifndef __SIMPLE_LOG_H__
#define __SIMPLE_LOG_H__

#undef ENABLED
#if defined(DEBUG)
  #define ENABLED 1
#else
  #define ENABLED 0
#endif

#include <string.h>

enum { 
  LOG_INFO, 
  LOG_DEBUG, 
  LOG_WARN,
  LOG_ERROR
};

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_info(...)  do { \
    if (ENABLED) log_printf(LOG_INFO , __FILENAME__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)
#define log_debug(...) do { \
    if (ENABLED) log_printf(LOG_DEBUG, __FILENAME__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)
#define log_warn(...)  do { \
    if (ENABLED) log_printf(LOG_WARN , __FILENAME__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)
#define log_error(...) do { \
    if (ENABLED) log_printf(LOG_ERROR, __FILENAME__, __LINE__, __func__, __VA_ARGS__); \
  } while (0)

extern void log_printf(int level, const char* file, int line, const char* fn, const char* fmt, ...); 

#endif//__SIMPLE_LOG_H__ 