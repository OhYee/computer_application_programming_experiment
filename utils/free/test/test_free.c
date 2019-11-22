#include "../../boolean/boolean.h"
#include "../../print/print.h"
#include "../free.h"
#include <stdio.h>

void err() {}
int  main() {
    boolean pass = T;

    mp_init(16 * sizeof(int), &err);

    int *array_1 = (int *)mp_new(sizeof(int) * 8);
    for (int i = 0; i < 8; ++i) {
        array_1[i] = i;
    }

    int *array_2 = (int *)mp_new(sizeof(int) * 8);
    for (int i = 0; i < 8; ++i) {
        array_2[i] = 10 + i;
    }

    int *array_3 = (int *)mp_new(sizeof(int) * 8);
    if (array_3 != NULL) {
        pass = F;
        print_err("want error, but it seems works good.\n");
    }

    for (int i = 0; i < 8; ++i) {
        if (array_1[i] != i) {
            pass = F;
            print_err("array_1[%d] = %d, excepted %d\n", i, array_1[i], i);
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (array_2[i] != 10 + i) {
            pass = F;
            print_err("array_2[%d] = %d, excepted %d\n", i, array_2[i], 10 + i);
        }
    }

    if (pass) {
        print_ok("All testcase passed\n");
        return 0;
    } else {
        print_err("Some error\n");
        return 1;
    }
}