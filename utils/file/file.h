#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *filename, const char *type);
int   read(FILE *f, char *s);