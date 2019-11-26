#include "../boolean/boolean.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#define compare_char_macro(a, b) (++compare_number, a - b)

void compare_init();
int  compare_char(char a, char b);
int  compare_string(char *a, char *b);