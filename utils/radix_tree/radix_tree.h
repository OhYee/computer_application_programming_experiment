#include "../bits/bits.h"
#include "../boolean/boolean.h"
#include "../free/free.h"
#include <memory.h>

typedef struct _radix_tree      radix_tree;
typedef struct _radix_tree_node radix_tree_node;

struct _radix_tree {
    radix_tree_node *root;
    int              k;
    bits *           temp;
};

radix_tree *rt_init(int k);
void        rt_add(radix_tree *rt, void *value, int size);
void        rt_print(radix_tree *rt);

struct _radix_tree_node {
    radix_tree_node **children;
    boolean           end_of_value; // is this node end of the value
    bits *            value;
};

radix_tree_node *rtn_init(int m);
radix_tree_node *rtn_add(radix_tree_node *rtn, bits *value, int k,
                         boolean memory);
void             rtn_print(radix_tree_node *rtn, int m);
int              pow2(int m);