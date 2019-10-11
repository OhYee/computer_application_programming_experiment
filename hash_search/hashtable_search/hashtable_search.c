#include "../../utils/utils.h"
#include <memory.h>
#include <time.h>

const char *       patterns_filename = "../test/patterns-127w.txt";
const char *       words_filename = "../test/words-98w.txt";
const char *       output_filename = "./result.txt";
const int          hash_table_size = 1 << 16;
const int          max_pattern_number = 1280000;
const int          max_string_length = 256;
const unsigned int memory_length =
    max_pattern_number *
        (sizeof(link *) + sizeof(linked_node) + max_string_length) +
    10000;
extern long long compare_number;

boolean compare(void *a, void *b) {
    return compare_string((char *)(a), (char *)(b)) == 0;
}

typedef struct ht {
    link **array;
    int    length;
} hash_table;

int hash(char *s, int limit) {
    unsigned int code = 0;
    char *       ptr = s;

    int param = 1;
    while (compare_char(*ptr, '\0') != 0) {
        // code = code ^ (*ptr);
        code += (param * (*ptr)) % limit;
        param = (param * 9999991) % limit;
        ++ptr;
    }
    code = (code ^ 9999901) % limit;
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

int main(int argc, char **argv) {
    clock_start();

    mp_init(memory_length, mp_exit);
    hash_table *ht = ht_init(hash_table_size);
    char *      temp = mp_new(max_string_length * sizeof(char));
    int         word_number = 0;
    int         word_exist_number = 0;

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while (read(f, temp)) {
        ht_add(ht, temp);
    }
    fclose(f);

    // for (int i = 0; i < (ht->length); ++i) {
    //     printf("%d %d\n", i, ht->array[i] == NULL ? 0 :
    //     ht->array[i]->length);
    // }

    f = open_file(words_filename, "r");
    while (read(f, temp)) {
        ++word_number;
        // if (word_number % 10000 == 0)
        //     printf("%d %fs %d ok\n", word_number, clock_duration(),
        //            word_exist_number);

        if (ht_exist(ht, temp)) {
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