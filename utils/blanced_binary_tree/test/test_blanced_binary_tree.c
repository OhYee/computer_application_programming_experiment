#include "../blanced_binary_tree.h"

int compare(void *a, void *b) {
    int *aa = (int *)a;
    int *bb = (int *)b;
    if (*aa == *bb) {
        return 0;
    } else if (*aa > *bb) {
        return 1;
    } else {
        return -1;
    }
}

int *num_init(int a) {
    int *num = mp_new(sizeof(int));
    *num = a;
    return num;
}

int main() {
    mp_init(1 << 16, mp_exit);
    avl_tree *root = at_init(compare);
    at_add(root, tn_init((void *)num_init(3)));
    at_add(root, tn_init((void *)num_init(2)));
    at_add(root, tn_init((void *)num_init(5)));
    at_add(root, tn_init((void *)num_init(7)));
    at_add(root, tn_init((void *)num_init(1)));
    at_add(root, tn_init((void *)num_init(4)));
    at_add(root, tn_init((void *)num_init(9)));
    at_add(root, tn_init((void *)num_init(6)));
    at_add(root, tn_init((void *)num_init(11)));
    at_add(root, tn_init((void *)num_init(12)));
    at_add(root, tn_init((void *)num_init(8)));
    at_add(root, tn_init((void *)num_init(10)));
    at_add(root, tn_init((void *)num_init(13)));

    at_print(root);
    return 0;
}