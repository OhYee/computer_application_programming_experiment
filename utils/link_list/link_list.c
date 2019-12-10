#include "link_list.h"
#include "../free/free.h"
#include <stdio.h>

// link node memory pool
linked_node *_link_node_unused = NULL;

link_list *lk_init() {
    link_list *lk = mp_new(sizeof(link_list));
    lk->head = lk->tail = NULL;
    lk->length = 0;
    return lk;
}

linked_node *lk_node(void *ptr) {
    linked_node *node = NULL;
    if (_link_node_unused == NULL) {
        node = mp_new(sizeof(linked_node));
    } else {
        node = _link_node_unused;
        _link_node_unused = _link_node_unused->next;
    }
    node->next = NULL;
    node->value = ptr;
    return node;
}

void lk_add(link_list *lk, void *ptr) {
    linked_node *node = lk_node(ptr);
    if (lk_empty(lk)) {
        lk->head = lk->tail = node;
    } else {
        lk->tail->next = node;
        lk->tail = node;
    }
    ++lk->length;
}

boolean lk_empty(link_list *lk) { return lk->head == NULL && lk->tail == NULL; }

void lk_remove(link_list *lk, linked_node *ptr) {
    linked_node *p = lk->head;

    if (p == ptr) {
        p = lk->head = ptr->next;
    } else {
        while (p != NULL && p->next != ptr) {
            p = p->next;
        }
        if (p != NULL && p->next == ptr) {
            p->next = ptr->next;
            --lk->length;
            ptr->next = _link_node_unused;
            _link_node_unused = ptr->next;
        }
    }
    if (lk->tail == ptr) {
        lk->tail = p;
    }
}

// search target in the link using compare function
linked_node *lk_search(link_list *lk, void *target,
                       boolean (*compare)(void *value, void *target)) {
    if (lk_empty(lk)) {
        return NULL;
    }
    linked_node *ptr = lk->head;

    while (ptr != NULL) {
        if (compare(ptr->value, target)) {
            break;
        }
        ptr = ptr->next;
    }
    return ptr;
}
