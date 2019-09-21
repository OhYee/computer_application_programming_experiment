#include "../boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct memory_pool {
    void *head;
    int   length;
    int   max_length;
    void (*error_callback)();
} memory_pool;

memory_pool mp;

void mp_exit() { exit(1); }

void mp_init(int max_pool_length, void (*error_callback)()) {
    mp.max_length = max_pool_length;
    mp.head = malloc(mp.max_length);
    mp.length = 0;
    mp.error_callback = error_callback;
}

void mp_info() {
    printf("memery_pool info:\n\tmax_length: %d\n\tnow_length: %d\n\taddress "
           "%p ~ %p ~ %p\n",
           mp.max_length, mp.length, mp.head, mp.head + mp.length,
           mp.head + mp.max_length);
}
int mp_get_length() { return mp.length; }
int mp_get_max_length() { return mp.max_length; }

void *mp_new(int length) {
    if (mp.length + length > mp.max_length) {
        printf("Can not make more memory. The memory pool is only %d bytes, "
               "and %d used, can not make more %d bytes\n",
               mp.max_length, mp.length, length);
        mp.error_callback();
        return NULL;
    }
    void *ptr = mp.head + mp.length;
    mp.length += length;
    return ptr;
}