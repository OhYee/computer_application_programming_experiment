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

extern uint64_t compare_number;
extern int      _radix_node_number;

#define k (2)
#define m (4)
#define max_pattern_number (1280000)
#define max_string_length (256)
#define max_string_byte (13359219)
#define memory_length                                                          \
    (max_string_byte + max_pattern_number * 2 *                                \
                           (sizeof(radix_tree_node) +                          \
                            sizeof(radix_tree_node *) * m + sizeof(bits))) +   \
        65536

int compare(void *a, void *b) { return compare_string(a, b); }

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

    // rt_print(rt);

    compare_init();

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

    fprintf(output,
            "%10d %10.2f "
            "%" PRIu64 " %7d %7d\n",
            _radix_node_number, (double)mp_get_length() / 1024, compare_number,
            word_number, word_exist_number);
    printf("%f s\n", clock_duration());

    // extern int _bits_string_num;
    // extern int _bits_string_mem;
    // extern int _bits_num;
    // extern int _bits_mem;

    // extern int _radix_node_number;
    // extern int _radix_strmem;
    // extern int _radix_nodemem;
    // extern int _radix_strnum;

    // printf("%d\n%d %d %d %d\n%d %d %d %d\n%d\n", memory_length,
    // _bits_string_num,
    //        _bits_string_mem, _bits_num, _bits_mem, _radix_node_number,
    //        _radix_strmem, _radix_nodemem, _radix_strnum,sizeof(bits));

    fclose(output);
    return 0;
}