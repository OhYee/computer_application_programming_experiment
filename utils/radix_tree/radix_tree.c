#include "radix_tree.h"

radix_tree *rt_init(int k) {
    radix_tree *rt = mp_new(sizeof(radix_tree));
    rt->k = k;
    rt->temp = bits_init();
    return rt;
}

void rt_add(radix_tree *rt, void *value, int size) {
    rt->temp->start = 0;
    rt->temp->end = size * 8;
    rt->temp->value = value;

    // printf("Add %s ", (char *)value);
    // bits_print(rt->temp);
    // printf("\n");

    rt->root = rtn_add(rt->root, rt->temp, rt->k, T);
}

boolean rt_exist(radix_tree *rt, void *value, int size) {
    rt->temp->start = 0;
    rt->temp->end = size * 8;
    rt->temp->value = value;

    // printf("Search %s ", (char *)value);
    // bits_print(rt->temp);
    // printf("\n");

    return rtn_exist(rt->root, rt->temp, rt->k);
}
void rt_print(radix_tree *rt) {
    rtn_print(rt->root, pow2(rt->k));
    printf("\n");
}