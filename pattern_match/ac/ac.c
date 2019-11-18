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

int compare(void *args, int i, int j) {
    ac_tree_node **args_nodes = (ac_tree_node **)(((void **)args)[1]);
    return args_nodes[j]->match_number - args_nodes[i]->match_number;
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
    char **        patterns = mp_new(max_pattern_number);
    ac_automaton * ac = ac_init(sizeof(ac_automaton *));
    ac_tree_node **nodes = mp_new(max_pattern_number * sizeof(ac_tree_node *));

    FILE *output = open_file(output_filename, "w");
    FILE *f = open_file(patterns_filename, "r");

    while ((l = read(f, temp)) != 0) {
        patterns[pattern_number] = mp_new(l + 1);
        strcpy(patterns[pattern_number], temp);
        nodes[pattern_number] = ac_add(ac, patterns[pattern_number]);
        ++pattern_number;
    }
    fclose(f);

    ac_build(ac);

    compare_init();

    f = open_file(string_filename, "r");
    char c;
    while (1) {
        c = fgetc(f);
        if (c == EOF) {
            break;
        }
            ac_match_char(ac, c);
    }
    fclose(f);

    void *args[] = {patterns, nodes};
    sort(0, pattern_number - 1, args, compare, swap);

    for (int i = 0; i < pattern_number; ++i) {
        fprintf(output, "%s\t%d\n", patterns[i], nodes[i]->match_number);
    }

    printf("%f s\n", clock_duration());
    fclose(output);
    return 0;
}