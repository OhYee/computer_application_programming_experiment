#include "link.h"
#include "../free/free.h"
#include <stdio.h>

link *lk_init() {
    link *lk = mp_new(sizeof(link));
    lk->head = lk->tail = NULL;
    lk->length = 0;
    return lk;
}

linked_node *lk_node(void *ptr) {
    linked_node *node = mp_new(sizeof(linked_node));
    node->next = NULL;
    node->value = ptr;
    return node;
}

void lk_add(link *lk, void *ptr) {
    linked_node *node = lk_node(ptr);
    if (lk_empty(lk)) {
        lk->head = lk->tail = node;
    } else {
        lk->tail->next = node;
        lk->tail = node;
    }
    ++lk->length;
}

boolean lk_empty(link *lk) { return lk->head == NULL && lk->tail == NULL; }

// search target in the link using compare function
linked_node *lk_search(link *lk, void *target,
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
