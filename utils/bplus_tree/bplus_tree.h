#include "../boolean/boolean.h"
#include "../free/free.h"
#include <memory.h>

typedef int (*compare_function)(void *, void *);

typedef struct _bplus_tree      bplus_tree;
typedef struct _bplus_tree_node bplus_tree_node;

struct _bplus_tree {
    int              m;       // 阶数
    bplus_tree_node *root;    // 根
    compare_function compare; // 比较函数
};

struct _bplus_tree_node {
    boolean is_leaf; // 是叶子节点
    int     num;     // 关键字/子树个数
    void ** keys;    // 关键字列表
    bplus_tree_node *
        *pointers; // 子树指针/当是叶子节点时，使用第0个作为指向下一个叶子的指针
};

bplus_tree *bpt_init(int m, compare_function compare);
void        bpt_add(bplus_tree *bpt, void *value, int size);
void        bpt_print(bplus_tree *bpt);
boolean     bpt_exist(bplus_tree *bpt, void *value);

bplus_tree_node *bptn_init(int max_length);
bplus_tree_node *bptn_next(bplus_tree_node *bptn);
// bptn_add_to_node add a value to this node.
// UNSAFE: ensure the node has enough space.
int bptn_add_to_node(bplus_tree_node *bptn, void *value,
                     compare_function compare);
/*
    bptn_split
    split b+ tree node
    @return a pointer to the new node (if no need for spliting, return NULL)
    */
bplus_tree_node *bptn_split(bplus_tree_node *bptn, int max_length);
int              bptn_search_index(bplus_tree_node *bptn, void *value,
                                   compare_function compare);
void *           bptn_get_extremum(bplus_tree_node *bptn);
bplus_tree_node *bptn_add(bplus_tree_node *bptn, void *value, int max_length,
                          compare_function compare);
void             bptn_print(bplus_tree_node *bptn);
boolean          bptn_exist(bplus_tree_node *bptn, void *value,
                            compare_function compare);