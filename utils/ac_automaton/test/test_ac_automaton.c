#include "../../print/print.h"
#include "../ac_automaton.h"

boolean judge(ac_tree_node *actn, ac_tree_node *failed) {
    if (actn->failed == failed) {
        return T;
    } else {
        print_err("Error at %p failed->%p, want failed->%p\n", actn, failed,
                  actn->failed);
        return F;
    }
}

int main() {
    boolean pass = T;
    mp_init(1 << 20, mp_exit);

    char *         string = "aababbcabcaacca";
    char *         patterns[] = {"a", "ab", "bab", "bc", "bca", "c", "caa"};
    int            want[] = {7, 3, 1, 2, 2, 4, 1};
    int            length = sizeof(patterns) / sizeof(char *);
    ac_tree_node **nodes = mp_new(length * sizeof(ac_tree_node *));

    ac_automaton *ac = ac_init();
    for (int i = 0; i < length; ++i) {
        nodes[i] = ac_add(ac, patterns[i]);
    }
    ac_build(ac);

    // ac_print(ac);
    pass &= judge(ac->root,  ac->root);

    pass &= judge(ac->root->children['a'], ac->root);
    pass &=
        judge(ac->root->children['a']->children['b'], ac->root->children['b']);

    pass &= judge(ac->root->children['b'], ac->root);
    pass &=
        judge(ac->root->children['b']->children['a'], ac->root->children['a']);
    pass &= judge(ac->root->children['b']->children['a']->children['b'],
                  ac->root->children['a']->children['b']);

    pass &=
        judge(ac->root->children['b']->children['c'], ac->root->children['c']);
    pass &= judge(ac->root->children['b']->children['c']->children['a'],
                  ac->root->children['c']->children['a']);

    pass &= judge(ac->root->children['c'], ac->root);
    pass &=
        judge(ac->root->children['c']->children['a'], ac->root->children['a']);
    pass &= judge(ac->root->children['c']->children['a']->children['a'],
                  ac->root->children['a']);

    char *c = string;
    while (*c != '\0') {
        ac_match_char(ac, *c);
        ++c;
    }

    for (int i = 0; i < length; ++i) {
        if (want[i] != nodes[i]->match_number) {
            print_err("'%s' matchs %d times, but want %d times\n", patterns[i],
                      nodes[i]->match_number, want[i]);
            pass = F;
        }
    }

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
    return 0;
}