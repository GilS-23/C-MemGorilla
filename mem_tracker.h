#pragma once
#ifndef MEM_TRACKER_H
#define MEM_TRACKER_H

#include <stdlib.h>
#include <stdio.h>

void* my_malloc(size_t size, const char* file, int line);
void* my_calloc(size_t nmemb, size_t size, const char* file, int line);
void* my_realloc(void* ptr, size_t size, const char* file, int line);
void my_free(void* ptr);

void print_leak_report();

#ifndef MEM_TRACKER_IMPLEMENTATION
#define malloc(size) my_malloc(size, __FILE__, __LINE__)
#define calloc(n, size) my_calloc(n, size, __FILE__, __LINE__)
#define realloc(ptr, size) my_realloc(ptr, size, __FILE__, __LINE__)
#define free(ptr) my_free(ptr)
#endif

#endif