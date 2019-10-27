#include "../boolean/boolean.h"
#include "../free/free.h"
#include <memory.h>

typedef struct _bits bits;

struct _bits {
    char *value;
    int   start;
    int   end;
};

bits *new_bits();
bits *bits_init_with_minimum_bytes(void *value, int start, int end);
bits *bits_sub(bits *b, int start, int end);
int   bits_get(bits *b, int pos);
int   bits_len(bits *b);
int   bits_prefix(bits *b1, bits *b2, int group_length);