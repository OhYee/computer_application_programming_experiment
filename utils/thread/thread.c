#include "thread.h"

thread_pool *tp_new(int thread_number, int mutex_number, thread_function tf) {
    thread_pool *tp = mp_new(sizeof(thread_pool));
    tp->thread_number = thread_number;
    tp->mutex_number = mutex_number;

    tp->thread_list = mp_new(sizeof(pthread_t) * thread_number);

    tp->mutex = mp_new(sizeof(pthread_mutex_t *) * mutex_number);
    for (int i = 0; i < tp->mutex_number; ++i) {
        tp->mutex[i] = mp_new(sizeof(pthread_mutex_t));
        pthread_mutex_init(tp->mutex[i], NULL);
    }

    for (int i = 0; i < tp->thread_number; ++i) {
        int ret = pthread_create(&tp->thread_list[i], NULL, tf, tp);
        if (ret != 0) {
            perror("pthread_create error:" + ret);
            exit(EXIT_FAILURE);
        }
    }

    return tp;
}

void tp_wait(thread_pool *tp) {
    for (int i = 0; i < tp->thread_number; ++i) {
        int ret = pthread_join(tp->thread_list[i], NULL);
        if (ret != 0) {
            perror("pthread_join error: " + ret);
            exit(EXIT_FAILURE);
        }
    }
}

void tp_lock(thread_pool *tp, int idx) {
    int ret = pthread_mutex_lock(tp->mutex[idx]);
    if (ret != 0) {
        perror("pthread_mutex_lock error: " + ret);
        exit(EXIT_FAILURE);
    }
}

void tp_unlock(thread_pool *tp, int idx) {
    int ret = pthread_mutex_unlock(tp->mutex[idx]);
    if (ret != 0) {
        perror("pthread_mutex_unlock error: " + ret);
        exit(EXIT_FAILURE);
    }
}