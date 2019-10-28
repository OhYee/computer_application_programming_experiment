#include "radix_tree.h"

radix_tree *rt_init(int k) {
    radix_tree *rt = mp_new(sizeof(radix_tree));
    rt->k = k;
    rt->temp = bits_init();
    return rt;
}

void rt_add(radix_tree *rt, void *value, int size) {
    printf("Add:\n");
    if (rt->root == NULL) {
        radix_tree_node *root = rtn_init(rt->k);
        root->value = bits_init_with_minimum_bytes(value, 0, size * 8);
        root->end_of_value = T;
        rt->root = root;
    } else {
        rt->temp->start = 0;
        rt->temp->end = size * 8;
        rt->temp->value = value;
        bits_print(rt->temp);
        printf("\n");

        rtn_add(rt->root, rt->temp, rt->k, T);
    }
}

void rt_print(radix_tree *rt) {
    rtn_print(rt->root, pow2(rt->k));
    printf("\n");
}