#include "../../boolean/boolean.h"
#include "../../print/print.h"
#include "../kmp.h"
#include <stdio.h>

int main() {
    boolean pass = T;
    char *  pattern = "ABCABCABCD";
    char *  string = "AABCABCABCABCDABCABCDABCABCABCDA";
    int     next[10];
    kmp_get_next(pattern, next);

    char *c = string;
    int   pos = 0;
    int   ans = 0;
    while (*c != '\0') {
        kmp_char(*(c++), pattern, &pos, next, &ans);
    }
    if (ans != 2) {
        print_err("error, want %d, got %d\n", 2, ans);
    }

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
}