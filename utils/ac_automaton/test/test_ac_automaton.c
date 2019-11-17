#include "../../print/print.h"
#include "../ac_automaton.h"

boolean judge(ac_tree_node *actn, char value, ac_tree_node *failed) {
    if (actn->value == value && actn->failed == failed) {
        return T;
    } else {
        print_err("Error at %c(%p) failed->(%c)%p, want %c(%p) "
                  "failed->(%c)%p\n",
                  value, actn, failed->value, failed, actn->value, actn,
                  actn->failed->value, actn->failed);
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
    pass &= judge(ac->root, '\0', ac->root);

    pass &= judge(ac->root->children['a'], 'a', ac->root);
    pass &= judge(ac->root->children['a']->children['b'], 'b',
                  ac->root->children['b']);

    pass &= judge(ac->root->children['b'], 'b', ac->root);
    pass &= judge(ac->root->children['b']->children['a'], 'a',
                  ac->root->children['a']);
    pass &= judge(ac->root->children['b']->children['a']->children['b'], 'b',
                  ac->root->children['a']->children['b']);

    pass &= judge(ac->root->children['b']->children['c'], 'c',
                  ac->root->children['c']);
    pass &= judge(ac->root->children['b']->children['c']->children['a'], 'a',
                  ac->root->children['c']->children['a']);

    pass &= judge(ac->root->children['c'], 'c', ac->root);
    pass &= judge(ac->root->children['c']->children['a'], 'a',
                  ac->root->children['a']);
    pass &= judge(ac->root->children['c']->children['a']->children['a'], 'a',
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