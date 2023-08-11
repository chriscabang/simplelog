/*
 */
#ifndef __SIMPLE_LOG_H__
#define __SIMPLE_LOG_H__

#undef ENABLED
#if defined(DEBUG)
  #define ENABLED 1
#else
  #define ENABLED 0
#endif

#define log_info(...) do { if (ENABLED) log_printf(DEBUG, __VA_ARGS__); } while (0)

#include <stdio.h>

extern void log_printf(int level, const char* fmt, ...); 

#endif//__SIMPLE_LOG_H__ 