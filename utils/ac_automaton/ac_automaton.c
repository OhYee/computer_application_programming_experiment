#include "ac_automaton.h"

ac_automaton *ac_init() {
    ac_automaton *ac = mp_new(sizeof(ac_automaton));
    ac->root = ac_tree_node_init('\0');
    ac->match = ac->root;
    return ac;
}

ac_tree_node *ac_add(ac_automaton *ac, char *s) {
    return ac_tree_node_add(ac->root, s);
}
void ac_build(ac_automaton *ac) {
    ac->root->failed = ac->root;
    ac->queue = lk_init();

    lk_add(ac->queue, ac->root);

    while (!lk_empty(ac->queue)) {
        ac_tree_node *parent = ac->queue->head->value;
        lk_remove(ac->queue, ac->queue->head);

        for (int i = 0; i < 256; ++i) {
            ac_tree_node *child = parent->children[i];
            if (child != NULL) {
                lk_add(ac->queue, child);

                ac_tree_node *ptr = parent->failed;
                while (
                    (ptr->children[i] == NULL || ptr->children[i] == child) &&
                    ptr != ac->root) {
                    ptr = ptr->failed;
                }
                if (ptr->children[i] != NULL && ptr->children[i] != child) {
                    child->failed = ptr->children[i];
                } else {
                    child->failed = ptr;
                }
            }
        }
    }
}

void ac_match_char(ac_automaton *ac, char c) {
    int idx = c;
    while (ac->match->children[idx] == NULL && ac->match != ac->root) {
        ac->match = ac->match->failed;
    }
    if (ac->match->children[idx] != NULL) {
        ac->match = ac->match->children[idx];
        ac_tree_node *p = ac->match;
        while (p != ac->root) {
            ++p->match_number;
            p = p->failed;
        }
    }
}

void ac_print(ac_automaton *ac) { ac_tree_node_print(ac->root, NULL); }

ac_tree_node *ac_tree_node_init(char value) {
    ac_tree_node *actn = mp_new(sizeof(ac_tree_node));
    actn->children = mp_new(256 * sizeof(ac_tree_node *));
    // actn->is_pattern_end = F;
    actn->value = value;
    actn->failed = NULL;
    actn->match_number = 0;
    memset(actn->children, 0, 256 * sizeof(ac_tree_node *));
    return actn;
}

ac_tree_node *ac_tree_node_add(ac_tree_node *actn, char *s) {
    int idx = *s;
    if (compare_char('\0', *(s)) == 0) {
        return actn;
    }
    if (actn->children[idx] == NULL) {
        actn->children[idx] = ac_tree_node_init(*s);
    }
    if (compare_char('\0', *(s + 1)) == 0) {
        // actn->children[idx]->is_pattern_end = T;
        return actn->children[idx];
    }
    return ac_tree_node_add(actn->children[idx], s + 1);
}

void ac_tree_node_print(ac_tree_node *actn, ac_tree_node *parent) {
    if (actn != NULL) {
        printf("%c(%p) failed->%p parent=%p\n", actn->value, actn, actn->failed,
               parent);
        for (int i = 0; i < 256; ++i) {
            ac_tree_node_print(actn->children[i], actn);
        }
    }
}
