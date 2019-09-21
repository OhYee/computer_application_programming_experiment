#include "../../utils/utils.h"
#include <memory.h>
#include <time.h>

const char *patterns_filename = "../testcase/patterns-127w_2.txt";
const char *words_filename = "../testcase/words-98w.txt";
const int   max_pattern_number = 1280000;
const int   max_string_length = 100;
const int   memory_length =
    max_pattern_number *
        (sizeof(link *) + sizeof(linked_node) + max_string_length) +
    10000;
extern long long compare_number;

boolean compare(void *a, void *b) {
    return compare_string((char *)(a), (char *)(b));
}

typedef struct ht {
    link **array;
    int    length;
} hash_table;

int hash(char *s, int limit) {
    unsigned int code = 0;
    char *       ptr = s;
    while (!compare_char(*ptr, '\0')) {
        code = code ^ (*ptr);
        ++ptr;
    }
    code = (code * 999983) % limit;
    return code;
}

hash_table *ht_init(int length) {
    hash_table *ht = mp_new(sizeof(hash_table));
    ht->length = length;
    ht->array = mp_new(ht->length * sizeof(link *));
    memset(ht->array, 0, ht->length * sizeof(link *));
    return ht;
}

void ht_add(hash_table *ht, char *s) {
    unsigned int code = hash(s, ht->length);
    link *       ptr = ht->array[code];

    if (ptr == NULL) {
        ptr = ht->array[code] = lk_init();
    }

    char *ss = mp_new(sizeof(char) * (strlen(s) + 1));
    strcpy(ss, s);
    lk_add(ptr, ss);
}

boolean ht_exist(hash_table *ht, char *s) {
    int   code = hash(s, ht->length);
    link *ptr = ht->array[code];

    if (ptr == NULL) {
        return F;
    }
    return NULL != lk_search(ptr, s, compare);
}

int main() {
    time_t start = clock();

    mp_init(memory_length, mp_exit);
    hash_table *ht = ht_init(10000);
    char *      temp = mp_new(max_string_length * sizeof(char));
    int         word_number = 0;
    int         word_exist_number = 0;

    FILE *f = open_file(patterns_filename);
    while (~fscanf(f, "%s", temp)) {
        ht_add(ht, temp);
    }
    fclose(f);

    // for (int i = 0; i < (ht->length); ++i) {
    //     printf("%d %d\n", i, ht->array[i] == NULL ? 0 :
    //     ht->array[i]->length);
    // }

    f = open_file(words_filename);
    while (~fscanf(f, "%s", temp)) {
        ++word_number;
        if (word_number % 10000 == 0)
            printf("%d %fs\n", word_number,
                   (double)(clock() - start) / CLOCKS_PER_SEC);

        if (ht_exist(ht, temp)) {
            ++word_exist_number;
            // printf("%s yes\n", temp);
        } else {
            // printf("%s no\n", temp);
        }
    }
    fclose(f);

    printf("%dKB, %lld times %d, %d\n", mp_get_length() / 1024, compare_number,
           word_number, word_exist_number);
    printf("%f s\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}