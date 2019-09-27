#include "../boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

FILE *  open_file(const char *filename, const char *type);
boolean read(FILE *f, char *s);