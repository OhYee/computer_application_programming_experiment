#include "radix_tree.h"

int pow2(int m) {
    int n = 1;
    while (m--) {
        n <<= 1;
    }
    return n;
}

int rtn_get_child_key(bits *value, int prefix, int k) {
    int l = bits_len(value);
    if (prefix >= l) {
        return -1;
    }
    int key = 0;
    for (int i = 0; i < k && i + prefix < l; ++i) {
        key = (key << 1) | bits_get(value, i + prefix);
    }
    return key;
}

radix_tree_node *rtn_init(int k) {
    radix_tree_node *rtn = mp_new(sizeof(radix_tree_node));
    rtn->children = mp_new(sizeof(radix_tree_node *) * pow2(k));
    return rtn;
}

radix_tree_node *rtn_add(radix_tree_node *rtn, bits *value, int k,
                         boolean memory) {
    int m = pow2(k);
    int l_node = bits_len(rtn->value);
    int l_value = bits_len(value);

    // get the prefix
    int prefix = bits_prefix(rtn->value, value, k);
    printf("prefix %d\n", prefix);
    if (prefix == -1) {
        // no prefix, value is same as this node.

        // this node is same as the value
        rtn->end_of_value = T;
        return NULL;
    }
    if (prefix < l_node) {
        // node need split
        int key = rtn_get_child_key(rtn->value, prefix, k);
        printf("node child key %d\n", key);

        bits *new_bits = bits_sub(rtn->value, prefix, bits_len(rtn->value));
        if (rtn->children[key] == NULL) {
            // child is null
            rtn->children[key] = rtn_init(m);
            rtn->children[key]->value = new_bits;
            rtn->children[key]->end_of_value = rtn->end_of_value;
        } else {
            // child is not empty
            rtn_add(rtn->children[key], new_bits, k, F);
        }
        // update this node
        rtn->value->end = prefix;
        rtn->end_of_value = F;
    }
    if (prefix < l_value) {
        // new value need split
        int key = rtn_get_child_key(value, prefix, k);
        printf("value child key %d\n", key);
        bits *new_bits;
        if (memory) {
            // the value need make memory
            new_bits = bits_init_with_minimum_bits(value);
        } else {
            new_bits = bits_sub(value, prefix, bits_len(value));
        }
        if (rtn->children[key] == NULL) {
            // child is null
            rtn->children[key] = rtn_init(k);
            rtn->children[key]->value = new_bits;
            rtn->children[key]->end_of_value = T;
        } else {
            // child is not empty
            rtn_add(rtn->children[key], new_bits, k, F);
        }
    }
    if (l_value < l_node && prefix == l_value) {
        rtn->end_of_value = T;
    }

    return NULL;
}

void rtn_print(radix_tree_node *rtn, int m) {
    if (rtn == NULL) {
        return;
    }
    printf("%p %d ", rtn, rtn->end_of_value);
    bits_print(rtn->value);
    printf("\n\t");
    for (int i = 0; i < m; ++i) {
        printf("%p ", rtn->children[i]);
    }
    printf("\n");

    for (int i = 0; i < m; ++i) {
        rtn_print(rtn->children[i], m);
    }
}