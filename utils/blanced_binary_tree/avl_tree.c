#include "blanced_binary_tree.h"

avl_tree *at_init(compare_function compare) {
    avl_tree *at = mp_new(sizeof(avl_tree));
    at->root = NULL;
    at->compare = compare;
    return at;
}

boolean at_search(avl_tree *at, void *value) {
    // printf("search %s\n", (char *)value);
    return tn_search(at->root, value, at->compare) != NULL;
}

void at_add(avl_tree *at, tree_node *value) {
    // printf("Add %s\n", (char *)value->value);
    at->root = tn_add(at->root, value, at->compare);
    // at_print(at);
}

void at_print(avl_tree *at) { tn_print(at->root); }
