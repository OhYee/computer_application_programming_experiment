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
    bpt_add(bpt, num(19), sizeof(int));
    bpt_add(bpt, num(18), sizeof(int));
    bpt_add(bpt, num(17), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(16), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(15), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(14), sizeof(int));
    bpt_print(bpt);

    return 0;
}