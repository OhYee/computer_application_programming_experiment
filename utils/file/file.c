#include "file.h"

FILE *open_file(const char *filename, const char *type) {
    FILE *f = fopen(filename, type);
    if (f == 0) {
        printf("Error: Can not open file %s.", filename);
        exit(1);
    }
    return f;
}

int read(FILE *f, char *s) {
    int   length = 0;
    char *ptr = s;
    char  c;

    while (1) {
        c = fgetc(f);
        if (c == EOF) {
            if (ptr == s) {
                return 0;
            } else {
                *(ptr) = '\0';
                return length;
            }
        }
        if (c == '\n') {
            if (ptr == s) {
                // continue;
                *(ptr++) = '\n';
                *(ptr++) = '\0';
                return 1;
            } else {
                *(ptr) = '\0';
                return length;
            }
        }
        *(ptr++) = c;
        ++length;
    }
}