#include "free.h"
#include "../boolean/boolean.h"

typedef struct memory_pool {
    void **          head;
    size_type_small *length;
    size_type_small *max_length;
    int              now_bucket;
    int              bucket_number;
    void (*error_callback)();
} memory_pool;

memory_pool mp;

void mp_exit() { exit(1); }

void mp_init(size_type_big max_pool_length, void (*error_callback)()) {
    mp.bucket_number = max_pool_length / (1 << 30) + 1;
    size_type_big left = max_pool_length;

    mp.head = malloc(mp.bucket_number * sizeof(void *));
    mp.length = malloc(mp.bucket_number * sizeof(size_type_small *));
    mp.max_length = malloc(mp.bucket_number * sizeof(size_type_small *));

    for (int i = 0; i < mp.bucket_number; ++i) {
        mp.length[i] = 0;
        if (left < (1 << 30)) {
            mp.head[i] = malloc(left);
            mp.max_length[i] = left;
            break;
        } else {
            mp.head[i] = malloc((1 << 30));
            left -= (1 << 30);
            mp.max_length[i] = (1 << 30);
        }
        if (mp.head[i] == NULL) {
            printf("init error. need " SIZE_TYPE_BIG_FORMAT " bytes\n",
                   max_pool_length);
            error_callback();
        }
    }

    // mp.head = malloc(mp.max_length);
    // mp.length = 0;
    mp.error_callback = error_callback;
}

void mp_info() {
    for (int i = 0; i < mp.bucket_number; ++i) {
        printf("bucket %3d, usage " SIZE_TYPE_SMALL_FORMAT
               "/" SIZE_TYPE_SMALL_FORMAT " %.2f%%, " SIZE_TYPE_SMALL_FORMAT
               " left\n",
               i, mp.length[i], mp.max_length[i],
               (mp.max_length[i] == 0
                    ? 100
                    : (double)mp.length[i] / mp.max_length[i] * 100),
               mp.max_length[i] - mp.length[i]);
    }
    printf("total: max_length: " SIZE_TYPE_BIG_FORMAT
           "  now_length: " SIZE_TYPE_BIG_FORMAT "\n",
           mp_get_max_length(), mp_get_length());
}
size_type_big mp_get_length() {
    size_type_big now_length = 0;
    for (int i = 0; i < mp.bucket_number; ++i) {
        now_length += mp.length[i];
    }
    return now_length;
}
size_type_big mp_get_max_length() {
    size_type_big max_length = 0;
    for (int i = 0; i < mp.bucket_number; ++i) {
        max_length += mp.max_length[i];
    }
    return max_length;
}

void *mp_new(size_type_small length) {
    int bucket;
    for (bucket = 0; bucket < mp.bucket_number; ++bucket) {
        if (mp.length[bucket] + length <= mp.max_length[bucket]) {
            void *ptr = mp.head[bucket] + mp.length[bucket];
            mp.length[bucket] += length;
            return ptr;
        }
    }

    printf("Can not make more memory. The memory pool is "
           "only " SIZE_TYPE_BIG_FORMAT " bytes, "
           "and " SIZE_TYPE_BIG_FORMAT
           " used, can not make more " SIZE_TYPE_SMALL_FORMAT " bytes\n",
           mp_get_max_length(), mp_get_length(), length);
    mp.error_callback();
    return NULL;
}