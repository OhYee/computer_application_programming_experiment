#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long size_type;
#define SIZE_TYPE_FORMAT "%llu"
#define __USE_MINGW_ANSI_STDIO 1

void      mp_init(size_type max_pool_length, void (*error_callback)());
size_type mp_get_length();
size_type mp_get_max_length();
void      mp_info();
void      mp_exit();
void *    mp_new(size_t length);