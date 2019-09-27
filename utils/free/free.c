#include "free.h"
#include "../boolean/boolean.h"

typedef struct memory_pool {
    void * head;
    size_t length;
    size_t max_length;
    void (*error_callback)();
} memory_pool;

memory_pool mp;

void mp_exit() { exit(1); }

void mp_init(size_t max_pool_length, void (*error_callback)()) {
    mp.max_length = max_pool_length;
    mp.head = malloc(mp.max_length);
    mp.length = 0;
    mp.error_callback = error_callback;
}

void mp_info() {
    printf("memery_pool info:\n\tmax_length: %zu\n\tnow_length: %zu\n\taddress "
           "%p ~ %p ~ %p\n",
           mp.max_length, mp.length, mp.head, mp.head + mp.length,
           mp.head + mp.max_length);
}
size_t mp_get_length() { return mp.length; }
size_t mp_get_max_length() { return mp.max_length; }

void *mp_new(size_t length) {
    if (mp.length + length > mp.max_length) {
        printf("Can not make more memory. The memory pool is only %zu bytes, "
               "and %zu used, can not make more %zu bytes\n",
               mp.max_length, mp.length, length);
        mp.error_callback();
        return NULL;
    }
    void *ptr = mp.head + mp.length;
    mp.length += length;
    return ptr;
}