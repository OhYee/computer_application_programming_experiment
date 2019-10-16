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

    int l = tn->left ? tn->left->deep : 0;
    int r = tn->right ? tn->right->deep : 0;
    if (abs(l - r) <= 1) {
        tn->deep = (l > r ? l : r) + 1;
    } else {
        if (l - r > 1) {
            return tn_right(tn);
        } else {
            return tn_left(tn);
        }
    }

    return tn;
}

char *tn_print(tree_node *tn) {
    if (tn == NULL) {
        return "NULL";
    } else {
        char *t = (char *)(tn->value);
        char *l = tn_print(tn->left);
        char *r = tn_print(tn->right);
        printf("    %s(%s)(%d)\n    ↙    ↘\n%s    %s\n\n", t,
               tn->parent ? (char *)(tn->parent->value) : "NULL", tn->deep, l, r);
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

tree_node *tn_left(tree_node *tn) {
    // printf("%s l\n", (char *)tn->value);
    tree_node *a = tn;
    tree_node *b = a->right;
    tree_node *c = b->left;

    tree_node *root = b;
    b->parent = a->parent;

    b->left = a;
    a->parent = b;

    a->right = c;
    if (c)
        c->parent = a;

    tn_update_deep(c);
    tn_update_deep(a);
    tn_update_deep(b);

    return root;
}

tree_node *tn_right(tree_node *tn) {
    // printf("%s r\n", (char *)tn->value);
    tree_node *a = tn;
    tree_node *b = a->left;
    tree_node *c = b->right;

    tree_node *root = b;
    b->parent = a->parent;

    b->right = a;
    a->parent = b;

    a->left = c;
    if (c)
        c->parent = a;

    tn_update_deep(c);
    tn_update_deep(a);
    tn_update_deep(b);

    return root;
}