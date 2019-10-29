#include "radix_tree.h"

int pow2(int m) {
    switch (m) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 8;
        default:
            break;
    }
    int t = pow2(m / 2);
    return t * t * (t % 2 ? 2 : 1);
}

int rtn_get_child_key(bits *value, int prefix, int k) {
    int l = bits_len(value);
    if (prefix > l) {
        print_err("Uncepted error: prefix %d and value is ", prefix);
        bits_print(value);
        print_err("\n");
        exit(1);
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
    if (rtn == NULL) {
        // if add to null, then make node
        rtn = rtn_init(m);
        rtn->end_of_value = T;
        if (memory) {
            rtn->value =
                bits_init_with_minimum_bits(value, value->start, value->end);
        } else {
            rtn->value = value;
        }
        return rtn;
    }

    int              l_node = bits_len(rtn->value);
    int              l_value = bits_len(value);
    radix_tree_node *root = rtn;

    // get the prefix
    int prefix = bits_prefix(rtn->value, value, k);
    if (prefix == l_node && prefix == l_value) {
        // value is same as this node.

        // this node is same as the value
        rtn->end_of_value = T;
        return rtn;
    }

    if (prefix < l_node) {
        // node need split
        int key = rtn_get_child_key(rtn->value, prefix, k);

        root = rtn_init(m);
        root->value = bits_sub(rtn->value, 0, prefix);
        root->end_of_value = F;
        root->children[key] = rtn;
        rtn->value->start +=  prefix;
    }

    if (prefix < l_value) {
        // new value need split
        int key = rtn_get_child_key(value, prefix, k);
        value->start += prefix;
        root->children[key] = rtn_add(root->children[key], value, k, memory);
    }

    return root;
}

boolean rtn_exist(radix_tree_node *rtn, bits *value, int k) {
    if (rtn == NULL) {
        return F;
    }

    int prefix = bits_prefix(rtn->value, value, k);
    if (prefix != bits_len(rtn->value)) {
        return F;
    }

    if (prefix == bits_len(value) && rtn->end_of_value == T) {
        return T;
    }

    int key = rtn_get_child_key(value, prefix, k);
    value->start += prefix;

    return rtn_exist(rtn->children[key], value, k);
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