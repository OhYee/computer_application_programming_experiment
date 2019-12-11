#include "../../utils/utils.h"
#include <pcre.h>

boolean compare(void *a, void *b) {
    return compare_string((char *)(a), (char *)(b)) == 0;
}

/*
    map
*/
typedef struct _map_node map_node;
typedef struct _map_list map_list;
typedef struct _map      map;

struct _map_node {
    char *    key;
    void *    value;
    int       index;
    map_node *next;
};

struct _map_list {
    map_node *head;
};

struct _map {
    map_list **hash_table;
    int        length;
};

int hash(char *s, int limit) {
    unsigned int code = 0;
    char *       ptr = s;

    int param = 1;
    while (compare_char(*ptr, '\0') != 0) {
        // code = code ^ (*ptr);
        code += (param * (*ptr)) % limit;
        param = (param * 9999991) % limit;
        ++ptr;
    }
    code = (code ^ 9999901) % limit;
    return code;
}

map *map_init(int length) {
    map *m = mp_new(sizeof(map));
    m->hash_table = mp_new(sizeof(map_list *) * length);
    m->length = length;
    for (int i = 0; i < m->length; ++i) {
        m->hash_table[i] = mp_new(sizeof(map_list));
        m->hash_table[i]->head = NULL;
    }
    return m;
}

map_node *map_add(map *m, char *value) {
    int       h = hash(value, m->length);
    map_list *lst = m->hash_table[h];
    if (lst == NULL) {
        lst = m->hash_table[h] = mp_new(sizeof(map_list));
        lst->head = NULL;
    }

    map_node *node = mp_new(sizeof(map_node));
    node->key = value;
    node->value = NULL;
    node->next = lst->head;
    lst->head = node->next;

    return node;
}

map_node *map_get(map *m, char *value) {
    int       h = hash(value, m->length);
    map_list *lst = m->hash_table[h];
    if (lst != NULL) {
        map_node *ptr = lst->head;
        while (ptr != NULL) {
            if (compare_string(ptr->key, value) == 0) {
                return ptr;
            }
            ptr = ptr->next;
        }
    }
    return NULL;
}

link_list *task_list; // 待爬取的页面列表
map *      relation;  // 页面关系
char       prefix[] = "/news.sohu.com";
boolean    has_data;
char **    strings;
int        strings_num;

char *get_url() {
    char *s = NULL;

    if (!lk_empty(task_list)) {
        linked_node *ptr = task_list->head;
        if (ptr != NULL) {
            s = (char *)ptr->value;
            lk_remove(task_list, task_list->head);
        }
    }

    // linked_node *ptr = task_list->head;
    // while (ptr != NULL) {
    //     printf("%s ", (char *)ptr->value);
    //     ptr = ptr->next;
    // }
    // printf("\n");

    return s;
}

void record_url(char *p, char *c, int length) {
    char *s = NULL;
    mp_new(sizeof(char) * (length + 1));
    memcpy(s, c, length);

    map_node *kv_pair;

    printf("record %s\n", s);

    kv_pair = map_get(relation, p);
    if (kv_pair == NULL) {
        char *pp = mp_new(sizeof(char) * (strlen(p) + 1));
        memcpy(pp, p, length);

        kv_pair = map_add(relation, pp);
        kv_pair->value = lk_init();
    }
    lk_add(kv_pair->value, s);

    kv_pair = map_get(relation, s);
    if (kv_pair == NULL) {
        lk_add(task_list, s);

        kv_pair = map_add(relation, s);
        kv_pair->value = lk_init();
    }
}

void *task(void *arg) {
    thread_pool *tp = arg;
    int          length = 1 << 30;
    int          res_length = 1000;
    char *       response = mp_new(length);
    const char * err_msg;
    int          err_pos;
    int *        reg_res = mp_new(sizeof(int) * res_length);

    while (1) {
        tp_lock(tp, 0);
        char *url = get_url();
        if (has_data) {
            tp_unlock(tp, 0);
        }

        if (url == NULL) {
            break;
        }

        printf("getting    %s\n", url);
        int l = get_page(prefix, url, "10.108.106.165", 80, response, length);
        printf("getting ok %s\n", url);

        pcre *re = pcre_compile(
            "http://news.sohu.com([A-Za-z0-9\\-\\_\\%%\\&\\?\\/\\=\\.]+)",
            PCRE_MULTILINE + PCRE_CASELESS, &err_msg, &err_pos, NULL);

        int start_offset = 0;
        while (pcre_exec(re, NULL, response, l, start_offset, 0, reg_res,
                         res_length) > 0) {
            if (has_data) {
                tp_lock(tp, 0);
            }
            record_url(url, response + reg_res[2], reg_res[3] - reg_res[2]);
            if (has_data) {
                tp_unlock(tp, 0);
            }

            start_offset = reg_res[3];
        }

        if (!has_data) {
            has_data = T;
            tp_unlock(tp, 0);
        }
    }
    return NULL;
}

int main() {
    int hash_length = 1 << 16;
    mp_init((size_type_big)1 << 35, mp_exit);
    task_list = lk_init();
    relation = map_init(hash_length);

    has_data = F;

    lk_add(task_list, "/");

    thread_pool *tp = tp_new(10, 1, task);
    tp_wait(tp);

    printf("ok\n");

    int count = 0;
    for (int i = 0; i < relation->length; ++i) {
        if (relation->hash_table[i] != NULL) {
            map_node *ptr = relation->hash_table[i]->head;
            while (ptr != NULL) {
                printf("%s %d\n", ptr->key, count++);
                ptr = ptr->value;
            }
        }
    }

    return 0;
}
