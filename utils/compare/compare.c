#include "../boolean/boolean.h"

long long compare_number = 0;
boolean   compare_char(char a, char b) {
    ++compare_number;
    return a == b;
}
boolean compare_string(char *a, char *b) {
    char *ptr_a = a, *ptr_b = b;
    while (compare_char(*ptr_a, *ptr_b) && *ptr_a != '\0' && *ptr_b != '\0') {
        ++ptr_a;
        ++ptr_b;
    }
    return *ptr_a == '\0' && *ptr_b == '\0';
}