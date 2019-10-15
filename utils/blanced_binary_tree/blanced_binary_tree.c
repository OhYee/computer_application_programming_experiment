#include "blanced_binary_tree.h"

avl_tree *at_init(compare_function compare) {
    avl_tree *at = mp_new(sizeof(avl_tree));
    at->root = NULL;
    at->compare = compare;
    return at;
}

boolean at_search(avl_tree *at, void *value) {
    return tn_search(at->root, value, at->compare) != NULL;
}

void at_add(avl_tree *at, tree_node *value) {
    printf("Add %d\n", *(int *)value->value);
    at->root = tn_add(at->root, value, at->compare);

    tree_node *ptr = value;
    tree_node *child = NULL;
    tree_node *grandchild = NULL;
    while (ptr != at->root) {
        grandchild = child;
        child = ptr;
        ptr = ptr->parent;
    }
    if (grandchild != NULL && child != NULL &&
        abs(at->root->left->deep - at->root->right->deep) > 1) {
        if (child == at->root->left) {
            if (grandchild == child->left) {
                printf("ll\n");
                at_ll(at);
            } else {
                printf("lr\n");
                at_lr(at);
            }
        } else {
            if (grandchild == child->left) {
                printf("rl\n");
                at_rl(at);
            } else {
                printf("rr\n");
                at_rr(at);
                printf("rr ok\n");

                at_print(at);
            }
        }
    }
}

void at_print(avl_tree *at) { tn_print(at->root); }

void at_ll(avl_tree *at) {
    tree_node *a = at->root;
    tree_node *b = at->root->left;
    tree_node *e = b->right;

    at->root = b;
    b->parent = NULL;

    b->right = a;
    a->parent = b;

    a->left = e;
    e->parent = a;
}

void at_lr(avl_tree *at) {
    tree_node *a = at->root;
    tree_node *b = at->root->left;
    tree_node *e = b->right;
    tree_node *j = e->left;
    tree_node *k = e->right;

    at->root = e;
    e->parent = NULL;

    e->left = b;
    b->parent = e;

    b->right = j;
    j->parent = b;

    e->right = a;
    a->parent = e;

    a->left = k;
    k->parent = a;
}

void at_rr(avl_tree *at) {
    tree_node *a = at->root;
    tree_node *b = at->root->right;
    tree_node *e = b->left;

    at->root = b;
    b->parent = NULL;

    b->left = a;
    a->parent = b;

    a->right = e;
    e->parent = a;

    tn_update_deep(e);
    tn_update_deep(a);
    tn_update_deep(b);
}

void at_rl(avl_tree *at) {
    tree_node *a = at->root;
    tree_node *b = at->root->right;
    tree_node *e = b->left;
    tree_node *j = e->right;
    tree_node *k = e->left;

    at->root = e;
    e->parent = NULL;

    e->right = b;
    b->parent = e;

    b->left = j;
    j->parent = b;

    e->left = a;
    a->parent = e;

    a->right = k;
    k->parent = a;
}