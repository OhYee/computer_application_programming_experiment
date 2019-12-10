#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file(const char *filename, const char *type);
int   read_file(FILE *f, char *s);