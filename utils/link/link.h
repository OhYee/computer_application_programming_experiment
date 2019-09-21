#include "../boolean/boolean.h"

typedef struct _node {
    void *value;
    void *next;
} linked_node;

typedef struct _link {
    linked_node *head;
    linked_node *tail;
    int          length;
} link;

link *lk_init();

linked_node *lk_node(void *ptr);

void lk_add(link *lk, void *ptr);

boolean lk_empty(link *lk);

// search target in the link using compare function
linked_node *lk_search(link *lk, void *target,
                       boolean (*compare)(void *value, void *target));
