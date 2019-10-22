#include "../../print/print.h"
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
    bpt_add(bpt, num(1), sizeof(int));
    bpt_add(bpt, num(1), sizeof(int));
    bpt_add(bpt, num(2), sizeof(int));
    bpt_add(bpt, num(3), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(4), sizeof(int));
    bpt_add(bpt, num(4), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(5), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(6), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(7), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(8), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(9), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(10), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(11), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(18), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(19), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(12), sizeof(int));
    bpt_print(bpt);

    bpt_add(bpt, num(13), sizeof(int));
    bpt_print(bpt);

    boolean pass = T;
    int     testcases[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18, 19};
    for (int i = 0; i < sizeof(testcases) / 8; ++i) {
        int n = testcases[i];
        if (bpt_exist(bpt, num(n)) == T) {
            print_ok("Search %d passed.\n", n);
        } else {
            print_err("Search %d has error!\n", n);
            pass = F;
        }
    }
    if (bpt_exist(bpt, num(0)) == F) {
        print_ok("Search %d passed.\n", 0);
    } else {
        print_err("Search %d has error!\n", 0);
        pass = F;
    }
    if (bpt_exist(bpt, num(23)) == F) {
        print_ok("Search %d passed.\n", 23);
    } else {
        print_err("Search %d has error!\n", 23);
        pass = F;
    }

    if (pass) {
        print_ok("All testcases passed.\n");
    } else {
        print_err("Has error!\n");
    }

    return 0;
}