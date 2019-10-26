#include "../../print/print.h"
#include "../bits.h"

int main() {
    mp_init(1 << 30, mp_exit);
    boolean pass = T;
    int     prefix;

    // 0110 1001  1100 0011
    bits *b = bits_init_with_minimum_bytes("\x69\xC3", 0, 16);
    bits *s1 = bits_sub(b, 4, 12); // 0011 0110
    bits *s2 = bits_sub(b, 3, 5);  // 0011 0110

    if ((prefix = bits_prefix(b, s1)) != 0) {
        print_err("prefix want 0, got %d\n", prefix);
        pass = F;
    }

    if ((prefix = bits_prefix(b, s1)) != 0) {
        print_err("prefix want 0, got %d\n", prefix);
        pass = F;
    }

    if ((prefix = bits_prefix(b, s2)) != 2) {
        print_err("prefix want 2, got %d\n", prefix);
        pass = F;
    }

    if (pass) {
        print_ok("All testcases passed.\n");
    } else {
        print_err("Some errors!\n");
    }
    return 0;
}