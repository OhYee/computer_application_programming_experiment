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

extern long long compare_number;

const int    max_pattern_number = 1280000;
const int    max_string_length = 256;
const size_t memory_length =
    sizeof(radix_tree) +
    max_pattern_number *
        (max_string_length * sizeof(radix_tree_node) + max_string_length) +
    65535;

int compare(void *a, void *b) { return compare_string(a, b); }

int  t = 0;
void rtn_test(radix_tree_node *rtn, int m) {
    if (rtn == NULL) {
        return;
    }
    if (bits_len(rtn->value) == 0) {
        ++t;
    }
    for (int i = 0; i < m; ++i) {
        rtn_test(rtn->children[i], m);
    }
}
void rt_test(radix_tree *rt) { rtn_test(rt->root, pow2(rt->k)); }

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));
    int   word_number = 0;
    int   word_exist_number = 0;

    radix_tree *rt = rt_init(2);

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while (read(f, temp)) {
        rt_add(rt, temp, strlen(temp));
        // rt_print(rt);
    }
    fclose(f);

    // rt_test(rt);
    // printf("%d\n", t);
    // rt_print(rt);

    f = open_file(words_filename, "r");
    while (read(f, temp)) {
        ++word_number;

        if (rt_exist(rt, temp, strlen(temp))) {
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