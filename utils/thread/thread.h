#include "../boolean/boolean.h"
#include "../free/free.h"
#include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>

typedef struct _thread_pool thread_pool;

typedef void *(*thread_function)(void *);

struct _thread_pool {
    int               thread_number;
    int               mutex_number;
    pthread_t *       thread_list;
    pthread_mutex_t **mutex;
};

thread_pool *tp_new(int thread_number, int mutex_number, thread_function tf);
void         tp_wait(thread_pool *tp);
void         tp_lock(thread_pool *tp, int idx);
void         tp_unlock(thread_pool *tp, int idx);