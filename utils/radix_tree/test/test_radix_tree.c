#include "../../print/print.h"
#include "../radix_tree.h"
#include <memory.h>

int main() {
    mp_init(1 << 30, mp_exit);
    boolean pass = T;

    radix_tree *rt = rt_init(2);
    rt_print(rt);
    rt_add(rt, "Oh", 2); // 01001111 01101000
    rt_print(rt);
    rt_add(rt, "My", 2); // 01001101 01111001
    rt_print(rt);
    rt_add(rt, "God", 3); // 01000111 01101111 01100100
    rt_print(rt);
    rt_add(rt, "My", 2); // 01001101 01111001
    rt_print(rt);

    /*
    
    1111001000010110
    1011001010011110
    111000101111011000100110
    1011001010011110



    */

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
}