#include "../boolean/boolean.h"
#include "../free/free.h"
#include <memory.h>

typedef struct _radix_tree      radix_tree;
typedef struct _radix_tree_node radix_tree_node;

struct _radix_tree {
    radix_tree_node *root;
};

struct _radix_tree_node {
    radix_tree_node **children;
    void *            value;
    int               length;
};

int get_prefix(void *a, int a_l, void *b, int b_l, int k);