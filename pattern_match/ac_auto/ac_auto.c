#include "../../utils/utils.h"
#include <memory.h>
#include <stdlib.h>
#include <time.h>

// #define debug

#ifdef debug
const char *patterns_filename = "../test/pattern_simple.txt";
const char *string_filename = "../test/string_simple.txt";
#else
const char *patterns_filename = "../test/pattern.txt";
const char *string_filename = "../test/string.txt";
#endif
const char *output_filename = "./result.txt";

extern uint64_t compare_number;
extern int      _avl_tree_node_number;

#define string_file_byte (919943484)
#define max_pattern_number (2256700)
#define max_string_length (256)
#define memory_length ((size_type_big)1 << 33)
// (max_pattern_number * max_string_length + (sizeof(ac_tree_node *) * 257) +
//  sizeof(ac_automaton))

int compare(void *args, int i, int j) {
    char **        args_patterns = (char **)(((void **)args)[0]);
    ac_tree_node **args_nodes = (ac_tree_node **)(((void **)args)[1]);

    int res = args_nodes[j]->match_number - args_nodes[i]->match_number;
    if (res == 0) {
        res = compare_string(args_patterns[i], args_patterns[j]);
    }
    return res;
}
void swap(void *args, int i, int j) {
    char **        args_patterns = (char **)(((void **)args)[0]);
    ac_tree_node **args_nodes = (ac_tree_node **)(((void **)args)[1]);

    char *temp_parrtern = args_patterns[i];
    args_patterns[i] = args_patterns[j];
    args_patterns[j] = temp_parrtern;

    ac_tree_node *temp_nodes = args_nodes[i];
    args_nodes[i] = args_nodes[j];
    args_nodes[j] = temp_nodes;
}

int main() {
    clock_start();

    mp_init(memory_length, mp_exit);
    char *temp = mp_new(max_string_length * sizeof(char));

    int            pattern_number = 0;
    int            l;
    char **        patterns = mp_new(max_pattern_number * sizeof(char *));
    ac_automaton * ac = ac_init(sizeof(ac_automaton));
    ac_tree_node **nodes = mp_new(max_pattern_number * sizeof(ac_tree_node *));

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    // double cost_time = 0;

    printf("patterns:\n");
    while ((l = read(f, temp)) != 0) {
        patterns[pattern_number] = mp_new(l + 1);
        strcpy(patterns[pattern_number], temp);
        nodes[pattern_number] = ac_add(ac, patterns[pattern_number]);
        ++pattern_number;

        // if (clock_duration() - cost_time > 0.01) {
        //     cost_time = clock_duration();
        //     printf("%d/%d %.2f%% %.2fs, %.2fs left\r", pattern_number,
        //            max_pattern_number,
        //            (double)pattern_number / max_pattern_number * 100, cost_time,
        //            cost_time * max_pattern_number / pattern_number - cost_time);
        // }
    }
    fclose(f);

    printf("\npatterns read ok\n");

    ac_build(ac);
    printf("build ok\n");

    compare_init();

    // int file_pos = 0;
    f = open_file(string_filename, "r");

    int   buf_size = 1 << 20;
    char *buf = mp_new(buf_size);

    while (!feof(f)) {
        fread(buf, buf_size, 1, f);
        char *c = buf;
        while (*c != '\0') {
            ac_match_char(ac, *c);
            ++c;

            // ++file_pos;
            // if (clock_duration() - cost_time > 0.01) {
            //     cost_time = clock_duration();
            //     printf("%d/%d %.2f%% %.2fs, %.2fs left\r", file_pos,
            //            string_file_byte,
            //            (double)file_pos / string_file_byte * 100, cost_time,
            //            cost_time * string_file_byte / file_pos - cost_time);
            // }
        }
    }
    printf("\n");

    fclose(f);

    int   compare_number_backup = compare_number;
    void *args[] = {patterns, nodes};
    sort(0, pattern_number - 1, args, compare, swap);
    compare_number = compare_number_backup;

    for (int i = 0; i < pattern_number; ++i) {
        fprintf(output, "%s\t%d\n", patterns[i], nodes[i]->match_number);
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
