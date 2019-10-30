#include "../boolean/boolean.h"
#include "../free/free.h"
#include <math.h>
#include <string.h>

typedef int (*compare_function)(void *, void *);

typedef struct _avl_tree_node avl_tree_node;
struct _avl_tree_node {
    void *     value;
    // avl_tree_node *parent;
    avl_tree_node *left;
    avl_tree_node *right;
    int        deep;
};

avl_tree_node *avl_tn_init(void *value);
avl_tree_node *avl_tn_search(avl_tree_node *avl_tn, void *value, compare_function compare);
avl_tree_node *avl_tn_add(avl_tree_node *avl_tn, avl_tree_node *value, compare_function compare);
avl_tree_node *avl_tn_left(avl_tree_node *avl_tn);
avl_tree_node *avl_tn_right(avl_tree_node *avl_tn);
char *     avl_tn_print(avl_tree_node *avl_tn);

typedef struct _avl_tree avl_tree;
struct _avl_tree {
    avl_tree_node *      root;
    compare_function compare;
};

avl_tree *at_init(compare_function compare);
boolean   at_search(avl_tree *at, void *value);
void      at_add(avl_tree *at, void *value, int size);
void      at_print(avl_tree *avl_tn);