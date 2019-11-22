#include "../../print/print.h"
#include "../blanced_binary_tree.h"

uint64_t compare_number = 0;
int      compare(void *a, void *b) {
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
    at_add(at, num_init(3), sizeof(int));
    at_add(at, num_init(2), sizeof(int));
    at_add(at, num_init(5), sizeof(int));
    at_add(at, num_init(7), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(4), sizeof(int));
    at_add(at, num_init(9), sizeof(int));
    at_add(at, num_init(6), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(8), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(2), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));
    at_add(at, num_init(1), sizeof(int));

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