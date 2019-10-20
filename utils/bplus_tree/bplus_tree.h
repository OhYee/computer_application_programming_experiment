#include "../boolean/boolean.h"
#include "../free/free.h"

typedef int (*compare_function)(void *, void *);

typedef struct _bplus_tree      bplus_tree;
typedef struct _bplus_tree_node bplus_tree_node;

struct _bplus_tree {
    int              m;    // 阶数
    bplus_tree_node *root; // 根
};

struct _bplus_tree_node {
    boolean           is_leaf;  // 是叶子节点
    int               num;      // 关键字/子树个数
    void **           keys;     // 关键字列表
    bplus_tree_node **pointers; // 子树指针/当是叶子节点时，使用第0个作为指向下一个叶子的指针
};