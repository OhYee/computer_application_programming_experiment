#pragma once
#include "../boolean/boolean.h"

typedef struct _node {
    void *value;
    void *next;
} linked_node;

typedef struct _link {
    linked_node *head;
    linked_node *tail;
    int          length;
    linked_node *unused;
} link_list;

link_list *  lk_init();
linked_node *lk_node(void *ptr);
void         lk_add(link_list *lk, void *ptr);
void         lk_remove(link_list *lk, linked_node *ptr);
boolean      lk_empty(link_list *lk);
// search target in the link using compare function
linked_node *lk_search(link_list *lk, void *target,
                       boolean (*compare)(void *value, void *target));
