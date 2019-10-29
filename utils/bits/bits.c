#include "bits.h"

bits *bits_init() {
    bits *b = mp_new(sizeof(bits));
    b->value = NULL;
    b->start = 0;
    b->end = 0;
    return b;
}
bits *bits_init_with_minimum_bytes(void *value, int start, int end) {
    bits *b = bits_init();
    int   start_byte = start / 8;
    int   end_byte = end / 8 + (end % 8 ? 1 : 0);
    b->value = mp_new(end_byte - start_byte);
    b->start = start - start_byte * 8;
    b->end = end - start_byte * 8;
    memcpy(b->value, value + start_byte, end_byte - start_byte);
    return b;
}

bits *bits_init_with_minimum_bits(bits *b, int start, int end) {
    bits *bb = bits_init();
    int   start_byte = start / 8;
    int   end_byte = end / 8 + (end % 8 ? 1 : 0);
    bb->value = mp_new(end_byte - start_byte);
    bb->start = start - start_byte * 8;
    bb->end = end - start_byte * 8;
    memcpy(bb->value, b->value + start_byte, end_byte - start_byte);
    return bb;
}

bits *bits_sub(bits *b, int start, int end) {
    if (end + b->start >= b->end || start + b->start >= b->end) {
        print_err("bits overflow in bits_sub()\n");
        exit(1);
    }
    bits *bb = mp_new(sizeof(bits));
    bb->value = b->value;
    bb->start = b->start + start;
    bb->end = b->start + end;
    return bb;
}
int bits_get(bits *b, int pos) {
    pos += b->start;
    if (pos >= b->end || pos < 0) {
        print_err("bits overflow in bits_get()\n");
        exit(1);
    }
    return (b->value[pos >> 3] >> (pos & 7)) & 1;
}
int bits_len(bits *b) { return b->end - b->start; }
int bits_prefix(bits *b1, bits *b2, int group_length) {
    int l1 = bits_len(b1);
    int l2 = bits_len(b2);
    int lmin = l1 < l2 ? l1 : l2;
    int prefix = 0;
    for (int i = 0; i < lmin; i += group_length) {
        int group_match = 0;
        for (int j = i; j - i < group_length && j < lmin; ++j) {
            if (bits_get(b1, j) == bits_get(b2, j)) {
                ++group_match;
            } else {
                break;
            }
        }
        if (group_match == group_length) {
            prefix += group_match;
        } else {
            break;
        }
    }
    return prefix;
}
void bits_print(bits *b) {
    printf("[%p %d %d]", b->value, b->start, b->end);
    for (int i = 0; i < bits_len(b); ++i) {
        printf("%d", bits_get(b, i));
    }
}