#include "blanced_binary_tree.h"

int              _avl_tree_node_number = 0;
int              _avl_tree_strmem = 0;
int              _avl_tree_nodemem = 0;
int              _avl_tree_strnum = 0;
extern uint64_t compare_number;

avl_tree_node *avl_tn_init(void *value, int size) {
    ++_avl_tree_node_number;

    char *s = mp_new(size);
    memcpy(s, value, size);
    ++_avl_tree_strnum;
    _avl_tree_strmem += size;

    avl_tree_node *avl_tn = mp_new(sizeof(avl_tree_node));
    _avl_tree_nodemem += sizeof(avl_tree_node);

    avl_tn->value = s;
    // avl_tn->parent = NULL;
    avl_tn->left = NULL;
    avl_tn->right = NULL;
    avl_tn->deep = 1;
    return avl_tn;
}

avl_tree_node *avl_tn_search(avl_tree_node *avl_tn, void *value,
                             compare_function compare) {
    if (avl_tn == NULL) {
        return NULL;
    }
    ++compare_number;

    int res = compare(avl_tn->value, value);
    if (res == 0) {
        return avl_tn;
    } else if (res > 0) {
        return avl_tn_search(avl_tn->left, value, compare);
    } else {
        return avl_tn_search(avl_tn->right, value, compare);
    }
}

avl_tree_node *avl_tn_add(avl_tree_node *avl_tn, void *value, int size,
                          compare_function compare) {
    if (avl_tn == NULL) {
        return avl_tn_init(value, size);
    }
    int res = compare(avl_tn->value, value);
    if (res > 0) {
        avl_tn->left = avl_tn_add(avl_tn->left, value, size, compare);
        // avl_tn->left->parent = avl_tn;
    } else if (res < 0) {
        avl_tn->right = avl_tn_add(avl_tn->right, value, size, compare);
        // avl_tn->right->parent = avl_tn;
    } else {
        // same value do nothing
        return avl_tn;
    }

    int l = avl_tn->left ? avl_tn->left->deep : 0;
    int r = avl_tn->right ? avl_tn->right->deep : 0;
    if (abs(l - r) <= 1) {
        avl_tn->deep = (l > r ? l : r) + 1;
    } else {
        if (l - r > 1) {
            return avl_tn_right(avl_tn);
        } else {
            return avl_tn_left(avl_tn);
        }
    }

    return avl_tn;
}

char *avl_tn_print(avl_tree_node *avl_tn) {
    if (avl_tn == NULL) {
        return "NULL";
    } else {
        char *t = (char *)(avl_tn->value);
        char *l = avl_tn_print(avl_tn->left);
        char *r = avl_tn_print(avl_tn->right);
        printf("    %s(%d)\n    ↙    ↘\n%s    %s\n\n", t, avl_tn->deep, l, r);
        return t;
    }
}

void avl_tn_update_deep(avl_tree_node *avl_tn) {
    if (avl_tn != NULL) {
        int l = avl_tn->left ? avl_tn->left->deep : 0;
        int r = avl_tn->right ? avl_tn->right->deep : 0;
        avl_tn->deep = (l > r ? l : r) + 1;
    }
}

avl_tree_node *avl_tn_left(avl_tree_node *avl_tn) {
    // printf("%s l\n", (char *)avl_tn->value);
    avl_tree_node *a = avl_tn;
    avl_tree_node *b = a->right;
    avl_tree_node *c = b->left;

    avl_tree_node *root = b;
    // b->parent = a->parent;

    b->left = a;
    // a->parent = b;

    a->right = c;
    // if (c)
    // c->parent = a;

    avl_tn_update_deep(c);
    avl_tn_update_deep(a);
    avl_tn_update_deep(b);

    return root;
}

avl_tree_node *avl_tn_right(avl_tree_node *avl_tn) {
    // printf("%s r\n", (char *)avl_tn->value);
    avl_tree_node *a = avl_tn;
    avl_tree_node *b = a->left;
    avl_tree_node *c = b->right;

    avl_tree_node *root = b;
    // b->parent = a->parent;

    b->right = a;
    // a->parent = b;

    a->left = c;
    // if (c)
    // c->parent = a;

    avl_tn_update_deep(c);
    avl_tn_update_deep(a);
    avl_tn_update_deep(b);

    return root;
}