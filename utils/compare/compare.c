#include "../boolean/boolean.h"

long long compare_number = 0;

int compare_char(char a, char b) {
    ++compare_number;
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

int compare_string(char *a, char *b) {
    char *ptr_a = a, *ptr_b = b;
    while (*ptr_a != '\0' && *ptr_b != '\0') {
        int res = compare_char(*ptr_a, *ptr_b);
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