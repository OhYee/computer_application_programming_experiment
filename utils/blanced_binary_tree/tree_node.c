#include "blanced_binary_tree.h"

tree_node *tn_init(void *value) {
    tree_node *tn = mp_new(sizeof(tree_node));
    tn->value = value;
    tn->parent = NULL;
    tn->left = NULL;
    tn->right = NULL;
    tn->deep = 1;
    return tn;
}

tree_node *tn_search(tree_node *tn, void *value, compare_function compare) {
    if (tn == NULL) {
        return NULL;
    }
    int res = compare(tn->value, value);
    if (res == 0) {
        return tn;
    } else if (res > 0) {
        return tn_search(tn->left, value, compare);
    } else {
        return tn_search(tn->right, value, compare);
    }
}

tree_node *tn_add(tree_node *tn, tree_node *value, compare_function compare) {
    if (tn == NULL) {
        return value;
    }
    int res = compare(tn->value, value->value);
    if (res > 0) {
        tn->left = tn_add(tn->left, value, compare);
        tn->left->parent = tn;
    } else if (res < 0) {
        tn->right = tn_add(tn->right, value, compare);
        tn->right->parent = tn;
    }
    tn_update_deep(tn);
    return tn;
}

int tn_print(tree_node *tn) {
    if (tn == NULL) {
        return -1;
    } else {
        int t = *(int *)(tn->value);
        int l = tn_print(tn->left);
        int r = tn_print(tn->right);
        printf("    %4d(%d)(%d)\n    ↙    ↘\n%4d    %4d\n\n", t,
               tn->parent ? *(int *)(tn->parent->value) : -1, tn->deep, l, r);
        return t;
    }
}

void tn_update_deep(tree_node *tn) {
    if (tn != NULL) {
        int l = tn->left ? tn->left->deep : 0;
        int r = tn->right ? tn->right->deep : 0;
        tn->deep = (l > r ? l : r) + 1;
    }
}