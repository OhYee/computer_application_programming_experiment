#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define __USE_MINGW_ANSI_STDIO 1

void   mp_init(size_t max_pool_length, void (*error_callback)());
size_t mp_get_length();
size_t mp_get_max_length();
void   mp_info();
void   mp_exit();
void * mp_new(size_t length);