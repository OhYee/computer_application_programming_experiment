#include "file.h"

FILE *open_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == 0) {
        printf("Error: Can not open file %s.", filename);
        exit(1);
    }
    return f;
}