#include "../boolean/boolean.h"
#include "../free/free.h"
#include <string.h>
#include <math.h>

typedef int (*compare_function)(void *, void *);

typedef struct _tree_node tree_node;
struct _tree_node {
    void *     value;
    tree_node *parent;
    tree_node *left;
    tree_node *right;
    int        deep;
};

tree_node *tn_init(void *value);
tree_node *tn_search(tree_node *tn, void *value, compare_function compare);
tree_node *tn_add(tree_node *tn, tree_node *value, compare_function compare);
int        tn_print(tree_node *tn);

typedef struct _avl_tree avl_tree;
struct _avl_tree {
    tree_node *      root;
    compare_function compare;
};

avl_tree *at_init(compare_function compare);
boolean   at_search(avl_tree *at, void *value);
void      at_add(avl_tree *at, tree_node *value);
void      at_print(avl_tree *tn);
void      at_ll(avl_tree *at);
void      at_lr(avl_tree *at);
void      at_rr(avl_tree *at);
void      at_rl(avl_tree *at);