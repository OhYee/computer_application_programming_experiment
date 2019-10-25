#include "../../print/print.h"
#include "../radix_tree.h"
#include <memory.h>

typedef struct _prefix_testcase {
    char *a;
    int   length_a;
    char *b;
    int   length_b;
    int   k;
    int   want;
} prefix_testcase;

prefix_testcase *new_prefix_testcase(char *a, int length_a, char *b,
                                     int length_b, int k, int want) {
    prefix_testcase *pt = mp_new(sizeof(prefix_testcase));

    return pt;
}

boolean test_prefix() {
    prefix_testcase testcases[] = {
        {a: "\x00", length_a: 8, b: "\x00", length_b: 8, k: 2, want: 8},
        {
            a: "\x0f\x0f", // 0000 1111  0000 1111
            length_a: 16,
            b: "\x0f\x07", // 0000 1111  0000 0111
            length_b: 16,
            k: 2,
            want: 10
        },
        {a: "\x0f", length_a: 8, b: "\x07", length_b: 8, k: 2, want: 2},
    };

    boolean pass = T;
    for (int i = 0; i < sizeof(testcases) / sizeof(prefix_testcase); ++i) {
        prefix_testcase *t = &testcases[i];
        int res = get_prefix(t->a, t->length_a, t->b, t->length_b, t->k);
        if (res != t->want) {
            print_err("Got %d but want %d\n", res, t->want);
            pass = F;
        }
    }
    return pass;
}

int main() {
    mp_init(1 << 30, mp_exit);
    boolean pass = T;
    pass &= test_prefix();

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
}