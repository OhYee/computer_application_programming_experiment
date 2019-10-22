#include "bplus_tree.h"

// index is the min value or the max value
#define MIN_VALUE

bplus_tree_node *bptn_init(int max_length) {
    bplus_tree_node *bptn = mp_new(sizeof(bplus_tree_node));
    bptn->keys = mp_new(sizeof(void *) * (max_length + 1));
    bptn->pointers = mp_new(sizeof(void *) * (max_length + 1));
    memset(bptn->pointers, 0, sizeof(void *) * (max_length + 1));
    bptn->num = 0;
    bptn->is_leaf = T;
    return bptn;
}
bplus_tree_node *bptn_next(bplus_tree_node *bptn) { return bptn->pointers[0]; }

// bptn_add_to_node add a value to this node.
// UNSAFE: ensure the node has enough space.
int bptn_add_to_node(bplus_tree_node *bptn, void *value,
                     compare_function compare) {
    int i = 0;

    // this value has been inserted
    for (i = 0; i < bptn->num; ++i) {
        if (compare(value, bptn->keys[i]) == 0) {
            return -1;
        }
    }

    for (i = bptn->num; i >= 1; --i) {
        int res = compare(value, bptn->keys[i - 1]);
        if (res == 1) {
            break;
        } else {
            bptn->keys[i] = bptn->keys[i - 1];
            bptn->pointers[i] = bptn->pointers[i - 1];
        }
    }
    bptn->keys[i] = value;
    bptn->pointers[i] = i == bptn->num ? NULL : bptn->pointers[i + 1];
    ++bptn->num;
    return i;
    // printf("unexcepted error: can find a appropriate space to add.\n");
    // exit(1);
    // return 0;
}

/*
    bptn_split
    split b+ tree node
    @return a pointer to the new node (if no need for spliting, return NULL)
    */
bplus_tree_node *bptn_split(bplus_tree_node *bptn, int max_length) {
    if (bptn->num > max_length) {
        // need split
        bplus_tree_node *bptn2 = bptn_init(max_length);
        bptn->num = ((max_length + 1) / 2) + ((max_length + 1) % 2);
        bptn2->num = max_length - bptn->num + 1;

        // move data to the new node
        for (int i = 0; i < bptn2->num; ++i) {
            bptn2->keys[i] = bptn->keys[bptn->num + i];
            bptn2->pointers[i] = bptn->pointers[bptn->num + i];
        }

        return bptn2;
    }
    return NULL;
}

int bptn_search_index(bplus_tree_node *bptn, void *value,
                      compare_function compare) {
    int i = 0;
    for (i = 0; i < bptn->num; ++i) {
        // find the first bigger value and insert
#ifdef MIN_VALUE
        // keys[i] > value
        if (compare(bptn->keys[i], value) > 0) {
            if (i == 0) {
                return 0;
            }
            return i - 1;
        }
#else
        // keys[i] >= value
        if (compare(bptn->keys[i], value) >= 0) {
            if (i == 0) {
                return 0;
            }
            return i;
        }
#endif
    }
    return bptn->num - 1;
}

void *bptn_get_extremum(bplus_tree_node *bptn) {
#ifdef MIN_VALUE
    return bptn->keys[0];
#else
    return bptn->keys[bptn->num - 1];
#endif
}

bplus_tree_node *bptn_add(bplus_tree_node *bptn, void *value, int max_length,
                          compare_function compare) {
    if (bptn->is_leaf) {
        // left
        // insert whatever
        bptn_add_to_node(bptn, value, compare);

        // splite (if need)
        bplus_tree_node *next = bptn_split(bptn, max_length);
        if (next != NULL) {
            bptn->pointers[0] = next; // next指针
        }
        return next;
    } else {
        // mid-node
        // find the sub-tree index
        int index = bptn_search_index(bptn, value, compare);
        if (compare(bptn->keys[index], value) == 0) {
            return NULL;
        }

        // insert whatever (recursive)
        bplus_tree_node *bptn2 =
            bptn_add(bptn->pointers[index], value, max_length, compare);

        // update the extremum
        bptn->keys[index] = bptn_get_extremum(bptn->pointers[index]);

        if (bptn2 != NULL) {
            // sub-tree has splited

            // insert the key to this node
            int idx = bptn_add_to_node(bptn, bptn_get_extremum(bptn2), compare);
            if (idx != -1) {
                bptn->pointers[idx] = bptn2;
            }

            // split (if need)
            bplus_tree_node *split_node = bptn_split(bptn, max_length);
            if (split_node != NULL) {
                split_node->is_leaf = F;
            }
            return split_node;
        }
    }
    return NULL;
}

void bptn_print(bplus_tree_node *bptn) {
    if (bptn == NULL)
        return;
    printf("Node %p | num %d | leaf %d\n", bptn, bptn->num, bptn->is_leaf);
    for (int i = 0; i < bptn->num; ++i) {
        printf("\t%s(%p)  ", (char *)bptn->keys[i], bptn->pointers[i]);
    }
    printf("\n");
    if (!bptn->is_leaf) {
        for (int i = 0; i < bptn->num; ++i) {
            bptn_print(bptn->pointers[i]);
        }
    }
}

boolean bptn_exist(bplus_tree_node *bptn, void *value,
                   compare_function compare) {
    int index = bptn_search_index(bptn, value, compare);
    if (compare(bptn->keys[index], value) == 0) {
        return T;
    } else if (bptn->is_leaf) {
        return F;
    }
    return bptn_exist(bptn->pointers[index], value, compare);
}