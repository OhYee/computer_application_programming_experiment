#include "../../utils/utils.h"
#include <memory.h>
#include <stdlib.h>
#include <time.h>

// #define debug

#ifdef debug
const char *patterns_filename = "../test/patterns.txt";
const char *words_filename = "../test/words.txt";
#else
const char *patterns_filename = "../test/patterns-127w.txt";
const char *words_filename = "../test/words-98w.txt";
#endif
const char *output_filename = "./result.txt";

typedef unsigned int group_type;
const int            group_type_size = sizeof(group_type) * 8;

typedef struct _bit_group {
    group_type *       bits;
    unsigned long long group_number;
} bit_group;

typedef struct _bloom_filter {
    bit_group *        value;
    unsigned int       hash_num;
    unsigned long long bit_length;
} bloom_filter;

#define max_pattern_number (1280000)
#define max_string_length (256)
#define hash_number (5)
#define memory_length                                                          \
    (sizeof(bit_group) + sizeof(bloom_filter) + 8 * bit_length + 65536)

static const unsigned long long bit_length = 1 << 26;

extern long long compare_number;

void bg_set(bit_group *bg, unsigned long long pos) {
    group_type *v = bg->bits;
    v[pos >> 3] |= 1 << (pos & 7);
}
int bg_read(bit_group *bg, unsigned long long pos) {
    group_type *v = bg->bits;
    return v[pos >> 3] & (1 << (pos & 7));
}

void bg_reset(bit_group *bg) {
    memset(bg->bits, 0, group_type_size * bg->group_number);
}

bit_group *bg_init(unsigned long long size) {
    bit_group *bg = mp_new(sizeof(bit_group));
    bg->group_number = size / group_type_size;
    bg->bits = mp_new(sizeof(group_type) * bg->group_number);
    bg_reset(bg);
    return bg;
}

char buf[64] = {0};
void bg_print(bit_group *bg) {
    for (int i = bg->group_number - 1; i >= 0; --i) {
        unsigned int num = *(bg->bits + i);
        int          pos = group_type_size;

        for (int j = 0; j < group_type_size; ++j) {
            buf[j] = '0';
        }
        buf[group_type_size + 1] = '\0';

        while (num) {
            buf[pos--] = (num % 2) + '0';
            num /= 2;
        }

        printf("%d(%s)", i, buf);
    }
}

bloom_filter *bf_init(unsigned int k, unsigned long long m) {
    bloom_filter *bf = mp_new(sizeof(bloom_filter));
    bf->hash_num = k;
    bf->bit_length = m;
    bf->value = bg_init(m);
    return bf;
}

const int prime[] = {9999901, 9999907, 9999929, 9999931, 9999937,
                     9999943, 9999971, 9999973, 9999991};

unsigned long long hash(int type, char *s, unsigned long long limit) {
    unsigned long long code = 0;
    char *             ptr = s;
    int                param = 1;
    int                p = prime[8 - type];

    while (compare_char(*ptr, '\0') != 0) {
        code = (code + (param * (*ptr)));
        param = (param * p);
        ++ptr;
    }

    code = (code ^ 9999901) % limit;

    return code;
}

void bf_add(bloom_filter *bf, char *s) {
    for (int i = 0; i < bf->hash_num; ++i) {
        int code = hash(i, s, bf->bit_length);
        // set bg code-th bit to 1
        bg_set(bf->value, code);
    }
}

boolean bf_exist(bloom_filter *bf, char *s) {
    boolean exist = T;
    for (int i = 0; i < bf->hash_num; ++i) {
        int code = hash(i, s, bf->bit_length);
        // set bg code-th bit to 1
        if (!bg_read(bf->value, code)) {
            exist = F;
            break;
        }
    }
    return exist;
}

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));
    int   word_number = 0;
    int   word_exist_number = 0;

    bloom_filter *bf = bf_init(hash_number, bit_length);

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while (read(f, temp)) {
        bf_add(bf, temp);
    }
    fclose(f);

    // for (int i = 0; i < (ht->length); ++i) {
    //     printf("%d %d\n", i, ht->array[i] == NULL ? 0 :
    //     ht->array[i]->length);
    // }

    // bg_print(bf->value);
    // printf("\n");

    f = open_file(words_filename, "r");
    while (read(f, temp)) {
        ++word_number;
        // if (word_number % 10000 == 0)
        //     printf("%d %fs %d ok\n", word_number, clock_duration(),
        //            word_exist_number);

        if (bf_exist(bf, temp)) {
            ++word_exist_number;
            fprintf(output, "%s yes\n", temp);
        } else {
            fprintf(output, "%s no\n", temp);
        }
    }
    fclose(f);

    fprintf(output, "%10.2f %10lld %7d %7d\n", (double)mp_get_length() / 1024,
            compare_number, word_number, word_exist_number);
    printf("%f s\n", clock_duration());
    fclose(output);
    return 0;
}