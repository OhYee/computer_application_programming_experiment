#include "bplus_tree.h"

bplus_tree *bpt_init(int m, compare_function compare) {
    bplus_tree *bpt = mp_new(sizeof(bplus_tree));
    bpt->m = m;
    bpt->root = NULL;
    bpt->compare = compare;
    return bpt;
}

void bpt_add(bplus_tree *bpt, void *value, int size) {
    void *p = mp_new(size);
    memcpy(p, value, size);
    if (bpt->root == NULL) {
        bplus_tree_node *root = bptn_init(bpt->m);
        root->keys[0] = p;
        root->pointers[0] = NULL;

        root->is_leaf = T;
        root->num = 1;

        bpt->root = root;
    } else {
        bplus_tree_node *split_node =
            bptn_add(bpt->root, p, bpt->m, bpt->compare);
        if (split_node != NULL) {
            bplus_tree_node *root = bptn_init(bpt->m);
            root->keys[0] = bptn_get_extremum(bpt->root);
            root->pointers[0] = bpt->root;
            root->keys[1] = bptn_get_extremum(split_node);
            root->pointers[1] = split_node;

            root->is_leaf = F;
            root->num = 2;

            bpt->root = root;
        }
    }
};

void bpt_print(bplus_tree *bpt) {
    bptn_print(bpt->root);
    printf("\n");
}

boolean bpt_exist(bplus_tree *bpt, void *value) {
    return bptn_exist(bpt->root, value, bpt->compare);
}