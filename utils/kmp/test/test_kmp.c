#include "../../boolean/boolean.h"
#include "../../print/print.h"
#include "../kmp.h"
#include <stdio.h>

boolean test_1() {
    char *pattern = "ABCABCABCD";
    char *string = "AABCABCABCABCDABCABCDABCABCABCDA";
    int   next[10];
    kmp_get_next(pattern, next);

    char *c = string;
    int   pos = 0;
    int   ans = 0;
    while (*c != '\0') {
        kmp_char(*(c++), pattern, &pos, next, &ans);
    }
    if (ans != 2) {
        print_err("test_1 error, want %d, got %d\n", 2, ans);
        return F;
    }
    return T;
}

boolean test_2() {
    char *pattern = "ABCABCDABCABCD";
    char *string = "DDABCABCDABCABCDABCABCDDD";
    int   next[15];
    kmp_get_next(pattern, next);

    char *c = string;
    int   pos = 0;
    int   ans = 0;
    while (*c != '\0') {
        kmp_char(*(c++), pattern, &pos, next, &ans);
    }
    if (ans != 2) {
        print_err("test_2 error, want %d, got %d\n", 2, ans);
        return F;
    }
    return T;
}

int main() {
    boolean pass = T;

    pass &= test_1();
    pass &= test_2();

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
}