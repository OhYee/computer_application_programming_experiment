#include "../../print/print.h"
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
    avl_tree *at = at_init(compare);
    at_add(at, tn_init((void *)num_init(3)));
    at_add(at, tn_init((void *)num_init(2)));
    at_add(at, tn_init((void *)num_init(5)));
    at_add(at, tn_init((void *)num_init(7)));
    at_add(at, tn_init((void *)num_init(1)));
    at_add(at, tn_init((void *)num_init(4)));
    at_add(at, tn_init((void *)num_init(9)));
    at_add(at, tn_init((void *)num_init(6)));
    at_add(at, tn_init((void *)num_init(11)));
    at_add(at, tn_init((void *)num_init(12)));
    at_add(at, tn_init((void *)num_init(8)));
    at_add(at, tn_init((void *)num_init(10)));
    at_add(at, tn_init((void *)num_init(13)));
    at_add(at, tn_init((void *)num_init(20)));
    at_add(at, tn_init((void *)num_init(14)));
    at_add(at, tn_init((void *)num_init(15)));
    at_add(at, tn_init((void *)num_init(16)));
    at_add(at, tn_init((void *)num_init(17)));
    at_add(at, tn_init((void *)num_init(18)));
    at_add(at, tn_init((void *)num_init(19)));

    at_print(at);

    boolean pass = T;

    if (at_search(at, (void *)num_init(10)) == T) {
        print_ok("search 10 ok\n");
    } else {
        print_err("search 10 error\n");
        pass = F;
    }
    if (at_search(at, (void *)num_init(100)) == F) {
        print_ok("search 100 ok\n");
    } else {
        print_err("search 100 error\n");
        pass = F;
    }
    if (at_search(at, (void *)num_init(1)) == T) {
        print_ok("search 1 ok\n");
    } else {
        print_err("search 1 error\n");
        pass = F;
    }

    if (pass) {
        print_ok("All testcases passed.\n");
    } else {
        print_err("Error!\n");
    }

    return 0;
}