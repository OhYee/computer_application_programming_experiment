#include "file.h"

FILE *open_file(const char *filename) {
    FILE *f = fopen(filename, "r");
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
            return F;
        }
        if (c == '\n') {
            if (ptr == s) {
                continue;
            }
            *(ptr) = '\0';
            return T;
        }
        *(ptr++) = c;
    }
}