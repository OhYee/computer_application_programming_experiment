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
extern int      _avl_tree_node_number;

#define max_pattern_number (1280000)
#define max_string_length (256)
#define max_string_byte (13359219)
#define memory_length                                                          \
    (sizeof(avl_tree) + max_pattern_number * sizeof(avl_tree_node) +           \
     max_string_byte + 65536)

int compare(void *a, void *b) { return compare_string(a, b); }

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));
    int   word_number = 0;
    int   word_exist_number = 0;

    avl_tree *at = at_init(compare);

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while (read_file(f, temp)) {
        at_add(at, temp, strlen(temp) + 1);
    }
    fclose(f);

    // at_print(at);

    compare_init();

    f = open_file(words_filename, "r");
    while (read_file(f, temp)) {
        ++word_number;

        if (at_search(at, temp)) {
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
            _avl_tree_node_number, (double)mp_get_length() / 1024,
            compare_number / 1000, word_number, word_exist_number);
    printf("%f s\n", clock_duration());
    fclose(output);
    return 0;
}