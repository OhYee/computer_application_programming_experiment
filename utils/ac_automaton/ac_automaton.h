#include "../boolean/boolean.h"
#include "../compare/compare.h"
#include "../free/free.h"
#include "../link/link.h"
#include <memory.h>

typedef struct _ac_automaton ac_automaton;
typedef struct _ac_tree_node ac_tree_node;

struct _ac_automaton {
    ac_tree_node *root;
    link *        queue;
    ac_tree_node *match;
};

struct _ac_tree_node {
    // char           value;
    ac_tree_node **children;
    ac_tree_node * failed;
    ac_tree_node * next; // 使用next可以提速25%,内存并没有多很多
    boolean        is_pattern_end;
    int            match_number;
};

ac_automaton *ac_init();
ac_tree_node *ac_add(ac_automaton *ac, char *s);
void          ac_build(ac_automaton *ac);
void          ac_print(ac_automaton *ac);
void          ac_match_char(ac_automaton *ac, char c);

ac_tree_node *ac_tree_node_init(char value);
ac_tree_node *ac_tree_node_add(ac_tree_node *actn, char *s);
void ac_tree_node_print(ac_tree_node *actn, ac_tree_node *parent, int value);