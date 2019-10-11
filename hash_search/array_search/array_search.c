#include "../../utils/utils.h"
#include <memory.h>
#include <time.h>

const char *patterns_filename = "../test/patterns-127w.txt";
const char *words_filename = "../test/words-98w.txt";
const char *output_filename = "./result.txt";

#define max_pattern_number (1280000)
#define max_string_length (256)
#define memory_length                                                          \
    (max_pattern_number * (sizeof(linked_node *) + 256) +                      \
     (max_string_length * sizeof(char)) + 10000)
     
extern long long compare_number;

boolean compare(void *a, void *b) {
    return compare_string((char *)(a), (char *)(b)) == 0;
}

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);

    link *lk = lk_init();

    char *temp = mp_new(max_string_length * sizeof(char));
    int   word_number = 0;
    int   word_exist_number = 0;

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");
    while (read(f, temp)) {
        char *s = mp_new(sizeof(char *) * (strlen(temp) + 1));
        strcpy(s, temp);
        lk_add(lk, s);
    }
    fclose(f);

    f = open_file(words_filename, "r");
    while (read(f, temp)) {
        ++word_number;
        // if (word_number % 10000 == 0)
        //     printf("%d %fs %d ok\n", word_number, clock_duration(),
        //            word_exist_number);

        if (NULL != lk_search(lk, temp, compare)) {
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