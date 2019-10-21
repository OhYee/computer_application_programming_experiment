#include "../bplus_tree.h"
#include <memory.h>

int compare(void *a, void *b) {
    int aa = *(int *)a;
    int bb = *(int *)b;
    if (aa == bb) {
        return 0;
    } else if (aa > bb) {
        return 1;
    } else {
        return -1;
    }
}

int *a;
int *num(int n) {
    memcpy(a, &n, sizeof(n));
    return a;
}

int main() {
    mp_init(1 << 20, mp_exit);
    a = mp_new(sizeof(int));
    bplus_tree *bpt = bpt_init(3, compare);
    bpt_add(bpt, num(20 - 1), sizeof(int));
    bpt_add(bpt, num(20 - 2), sizeof(int));
    bpt_add(bpt, num(20 - 3), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 4), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 5), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 6), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 7), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 8), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 9), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 10), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 11), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 18), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 19), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 12), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(20 - 13), sizeof(int));
    bpt_print(bpt);

    return 0;
}