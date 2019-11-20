#include "../../utils/utils.h"
#include <memory.h>
#include <stdlib.h>
#include <time.h>

// #define debug

#ifdef debug
const char *patterns_filename = "../test/pattern_simple.txt";
const char *string_filename = "../test/string_simple.txt";
#else
const char *patterns_filename = "../test/pattern_bf_kmp.txt";
const char *string_filename = "../test/string.txt";
#endif
const char *output_filename = "./result.txt";

extern uint64_t compare_number;
extern int       _avl_tree_node_number;

#define string_file_byte (919943484)
#define max_pattern_number (1600)
#define max_string_length (256)
#define memory_length (max_pattern_number * max_string_length) + (1 << 20)

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
    double cost_time = 0;

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));

    int pattern_number = 0;
    int l;
    patterns = mp_new(max_pattern_number * sizeof(char *));
    next = mp_new(max_pattern_number * sizeof(int *));

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    printf("patterns:\n");
    while ((l = read(f, temp)) != 0) {
        patterns[pattern_number] = mp_new(l + 1);

        next[pattern_number] = mp_new(l * sizeof(int));
        kmp_get_next(temp, next[pattern_number]);

        strcpy(patterns[pattern_number++], temp);

        if (clock_duration() - cost_time > 0.01) {
            cost_time = clock_duration();
            printf("%d/%d %.2f%% %.2fs, %.2fs left\r", pattern_number,
                   max_pattern_number,
                   (double)pattern_number / max_pattern_number * 100, cost_time,
                   cost_time * max_pattern_number / pattern_number - cost_time);
        }
    }
    fclose(f);
    printf("\npatterns read ok\n");

    count = mp_new(pattern_number * sizeof(int));
    pos = mp_new(pattern_number * sizeof(int));
    for (int i = 0; i < pattern_number; ++i) {
        count[i] = pos[i] = 0;
    }

    compare_init();

    int file_pos = 0;
    f = open_file(string_filename, "r");

    int   buf_size = 1 << 20;
    char *buf = mp_new(buf_size);

    while (!feof(f)) {
        fread(buf, buf_size, 1, f);
        char *c = buf;
        while (*c != '\0') {
            for (int i = 0; i < pattern_number; ++i) {
                match(*c, i);
            }

            ++c;

            ++file_pos;
            if (clock_duration() - cost_time > 0.01) {
                cost_time = clock_duration();
                printf("%d/%d %.2f%% %.2fs, %.2fs left\r", file_pos,
                       string_file_byte,
                       (double)file_pos / string_file_byte * 100, cost_time,
                       cost_time * string_file_byte / file_pos - cost_time);
            }
        }
    }
    fclose(f);

    void *args[] = {patterns, count};
    sort(0, pattern_number - 1, args, compare, swap);

    for (int i = 0; i < pattern_number; ++i) {
        fprintf(output, "%s\t%d\n", patterns[i], count[i]);
    }

    fprintf(output,
            "%10.2f "
            "%" PRIu64 "\n",
            (double)mp_get_length() / 1024, compare_number);
    printf("%f s\n", clock_duration());
    mp_info();
    fclose(output);
    return 0;
}