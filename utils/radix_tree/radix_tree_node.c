#include "radix_tree.h"

int get_prefix(void *a, int a_l, void *b, int b_l, int k) {
    char *aa = a;
    char *bb = b;
    int   m_l = a_l < b_l ? a_l : b_l;
    int   mask = (1 << k) - 1;
    int   byte_num = (m_l / 8) + (m_l % 8 ? 1 : 0);
    int   prefix = 0;
    for (int i = 0; i < byte_num; ++i) {
        if ((aa[i] ^ bb[i]) == 0) {
            prefix += 8;
        } else {
            for (int j = 0; j < 8 / k; ++j) {
                // ! make sure j is 1 2 4 8
                char mask_a = (aa[i] >> (j * k )) & mask;
                char mask_b = (bb[i] >> (j * k )) & mask;
                if ((mask_a ^ mask_b) == 0) {
                    prefix += k;
                } else {
                    break;
                }
            }
            break;
        }
    }
    return prefix;
}
