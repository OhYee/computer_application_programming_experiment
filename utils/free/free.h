#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t  size_type_small;
typedef uint64_t size_type_big;

#define SIZE_TYPE_SMALL_FORMAT "%" PRId32
#define SIZE_TYPE_BIG_FORMAT "%" PRIu64

#define __USE_MINGW_ANSI_STDIO 1

void          mp_init(size_type_big max_pool_length, void (*error_callback)());
size_type_big mp_get_length();
size_type_big mp_get_max_length();
void          mp_info();
void          mp_exit();
void *        mp_new(size_type_small length);