#include "../../utils/utils.h"
#include <memory.h>
#include <stdlib.h>
#include <time.h>

#define debug

#ifdef debug
const char *patterns_filename = "../test/pattern_simple.txt";
const char *string_filename = "../test/string_simple.txt";
#else
const char *patterns_filename = "../test/patterns-127w.txt";
const char *words_filename = "../test/words-98w.txt";
#endif
const char *output_filename = "./result.txt";

extern long long compare_number;
extern int       _avl_tree_node_number;

#define max_pattern_number (2256700)
#define max_string_length (256)
#define memory_length (max_pattern_number * max_string_length)

char **patterns;
int *  count;
int *  pos;
int ** next;

void match(char c, int index) {
    kmp_char(c, patterns[index], &pos[index], next[index], &count[index]);
}

int compare(void *args, int i, int j) {
    int *args_count = (int *)(((void **)args)[1]);
    return args_count[j] - args_count[i];
}
void swap(void *args, int i, int j) {
    char **args_patterns = (char **)(((void **)args)[0]);
    int *  args_count = (int *)(((void **)args)[1]);

    char *temp_parrtern = args_patterns[i];
    args_patterns[i] = args_patterns[j];
    args_patterns[j] = temp_parrtern;

    int temp_count = args_count[i];
    args_count[i] = args_count[j];
    args_count[j] = temp_count;
}

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));

    int pattern_number = 0;
    int l;
    patterns = mp_new(max_pattern_number);
    next = mp_new(max_pattern_number);

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while ((l = read(f, temp)) != 0) {
        patterns[pattern_number] = mp_new(l + 1);

        next[pattern_number] = mp_new(l * sizeof(int));
        kmp_get_next(temp, next[pattern_number]);

        strcpy(patterns[pattern_number++], temp);
    }
    fclose(f);

    count = mp_new(pattern_number * sizeof(int));
    pos = mp_new(pattern_number * sizeof(int));
    for (int i = 0; i < pattern_number; ++i) {
        count[i] = pos[i] = 0;
    }

    compare_init();

    f = open_file(string_filename, "r");
    char c;
    while (1) {
        c = fgetc(f);
        if (c == EOF) {
            break;
        }
        for (int i = 0; i < pattern_number; ++i) {
            match(c, i);
        }
    }
    fclose(f);

    void *args[] = {patterns, count};
    sort(0, pattern_number - 1, args, compare, swap);

    for (int i = 0; i < pattern_number; ++i) {
        fprintf(output, "%s\t%d\n", patterns[i], count[i]);
    }

    printf("%f s\n", clock_duration());
    fclose(output);
    return 0;
}