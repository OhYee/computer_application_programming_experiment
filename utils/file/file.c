#include "file.h"

FILE *open_file(const char *filename, const char *type) {
    FILE *f = fopen(filename, type);
    if (f == 0) {
        printf("Error: Can not open file %s.", filename);
        exit(1);
    }
    return f;
}

boolean read(FILE *f, char *s) {
    char *ptr = s;
    char  c;

    while (1) {
        c = fgetc(f);
        if (c == EOF) {
            if (ptr == s) {
                return F;
            } else {
                *(ptr) = '\0';
                return T;
            }
        }
        if (c == '\n') {
            if (ptr == s) {
                continue;
            } else {
                *(ptr) = '\0';
                return T;
            }
        }
        *(ptr++) = c;
    }
}