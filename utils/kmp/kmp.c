#include "kmp.h"

void kmp_get_next(char *s, int *next) {
    next[0] = -1;

    for (int i = 1;; ++i) {
        if (s[i] == '\0')
            break;
        int t = next[i - 1];
        while (t != -1 && s[t] != s[i - 1])
            t = next[t];
        next[i] = (s[i - 1] == s[t] ? t + 1 : 0);
    }
}

void kmp_char(char c, char *pattern, int *pattern_pos, int *next, int *ans) {
    while (*pattern_pos != -1 && c != pattern[*pattern_pos])
        *pattern_pos = next[*pattern_pos];
    if (pattern[++(*pattern_pos)] == '\0') {
        ++(*ans);
        *pattern_pos =
            next[*pattern_pos - 1] + (next[*pattern_pos - 1] == 0 ? 0 : 1);
    }
}
