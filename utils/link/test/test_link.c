#include "../../compare/compare.h"
#include "../../free/free.h"
#include "../../print/print.h"
#include "../link.h"
#include "stdio.h"
#include <memory.h>

boolean compare(void *a, void *b) {
    return compare_string((char *)(a), (char *)(b)) == 0;
}

int main() {
    mp_init(1024 * 4, mp_exit);
    char *s;

    link *lk = lk_init();
    if (!lk_empty(lk)) {
        print_err("link need be empty, but it seems not\n");
    }

    s = mp_new(5 * sizeof(char));
    memcpy(s, "abcd", 5);
    lk_add(lk, s);

    s = mp_new(5 * sizeof(char));
    memcpy(s, "ABCD", 5);
    lk_add(lk, s);

    s = mp_new(5 * sizeof(char));
    memcpy(s, "2333", 5);
    lk_add(lk, s);

    s = mp_new(5 * sizeof(char));
    memcpy(s, "666", 3);
    lk_add(lk, s);

    linked_node *res = lk_search(lk, "ABCD", compare);
    if (res != NULL) {
        print_ok("Find successly at %p(%s)\n", res, res->value);
    } else {
        print_err("Can not find value\n");
    }

    lk_remove(lk, res);

    res = lk_search(lk, "ABCD", compare);
    if (res == NULL) {
        print_ok("Can not find value\n");
    } else {
        print_err("Unwanted found %s at %p\n", res->value, res);
    }

    res = lk_search(lk, "CC", compare);
    if (res == NULL) {
        print_ok("Can not find value\n");
    } else {
        print_err("Unwanted found %s at %p\n", res->value, res);
    }

    linked_node *ptr = lk->head;
    while (ptr != NULL) {
        print_ok("%p %s\n", ptr, ptr->value);
        ptr = ptr->next;
    }

    return 0;
}