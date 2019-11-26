#include "compare.h"
uint64_t compare_number = 0;

void       compare_init() { compare_number = 0; }
inline int compare_char(char a, char b) { return compare_char_macro(a, b); }

int compare_string(char *a, char *b) {
    char *ptr_a = a, *ptr_b = b;
    while (*ptr_a != '\0' && *ptr_b != '\0') {
        int res = compare_char_macro(*ptr_a, *ptr_b);
        if (res != 0) {
            return res;
        }
        ++ptr_a;
        ++ptr_b;
    }
    if (*ptr_a != '\0') {
        return 1;
    } else if (*ptr_b != '\0') {
        return -1;
    } else {
        return 0;
    }
}