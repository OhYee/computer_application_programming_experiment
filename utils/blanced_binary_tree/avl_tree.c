#include "blanced_binary_tree.h"

avl_tree *at_init(compare_function compare) {
    avl_tree *at = mp_new(sizeof(avl_tree));
    at->root = NULL;
    at->compare = compare;
    return at;
}

boolean at_search(avl_tree *at, void *value) {
    // printf("search %s\n", (char *)value);
    return avl_tn_search(at->root, value, at->compare) != NULL;
}

void at_add(avl_tree *at, void *value, int size) {
    // printf("Add %s\n", (char *)value->value);
    // void *data = mp_new(size);
    // memcpy(data, value, size);
    // avl_tree_node *td = avl_tn_init(data);

    at->root = avl_tn_add(at->root, value, size, at->compare);
    // at_print(at);
}

void at_print(avl_tree *at) { avl_tn_print(at->root); }
