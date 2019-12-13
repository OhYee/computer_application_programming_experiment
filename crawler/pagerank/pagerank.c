#include "../../utils/utils.h"
#include <math.h>
#include <stdio.h>

#define MAX_URL_NUMBER 337800
#define eps 1e-11

char **idx2string;
int    url_number = 0;

link_list **relation_cp;
int *       out_number;
double *    pagerank;

int compare(void *args, int i, int j) {
    if (pagerank[i] > pagerank[j]) {
        return -1;
    } else if (pagerank[i] < pagerank[j]) {
        return 1;
    }
    return 0;
    return pagerank[j] > pagerank[i] ? 1 : 0;
}

void swap(void *args, int i, int j) {
    char *temp_idx2string = idx2string[i];
    idx2string[i] = idx2string[j];
    idx2string[j] = temp_idx2string;

    double temp_pagerank = pagerank[i];
    pagerank[i] = pagerank[j];
    pagerank[j] = temp_pagerank;
}

int main() {
    clock_start();
    mp_init((size_type_big)1 << 35, mp_exit);

    idx2string = mp_new(sizeof(char *) * MAX_URL_NUMBER);

    char *temp = mp_new(1 << 16);
    int   temp_id;

    // read string
    FILE *f = open_file("./urllist.txt", "r");
    while (fscanf(f, "%s %d", temp, &temp_id) != EOF) {
        int l = strlen(temp);
        idx2string[temp_id] = mp_new(sizeof(char) * (l + 1));
        strcpy(idx2string[temp_id], temp);
        url_number = temp_id + 1;
    }
    fclose(f);
    printf("urllist ok\n");

    relation_cp = mp_new(sizeof(link_list *) * url_number);
    out_number = mp_new(sizeof(int) * url_number);
    for (int i = 0; i < url_number; ++i) {
        relation_cp[i] = lk_init();
        out_number[i] = 0;
    }

    // read relation
    f = open_file("./urlcp.txt", "r");
    int c, p;
    while (fscanf(f, "%d - %d", &p, &c) != EOF) {
        int *pp = mp_new(sizeof(int));
        *pp = p;

        lk_add(relation_cp[c], pp);
        ++out_number[p];
    }
    fclose(f);
    printf("urlcp ok\n");

    pagerank = mp_new(sizeof(double) * url_number);
    for (int i = 0; i < url_number; ++i) {
        pagerank[i] = 1.0;
    }

    double delta = 0.0;

    while (1) {
        delta = 0.0;
        for (int i = 0; i < url_number; ++i) {
            double sum = 0;

            linked_node *ptr = relation_cp[i]->head;
            while (ptr != NULL) {
                int parent = *(int *)ptr->value;
                sum += pagerank[parent] / out_number[parent];

                ptr = ptr->next;
            }
            sum = 0.5 + 0.5 * sum;

            double delta_abs = fabs(pagerank[i] - sum);
            delta = fmax(delta, delta_abs);

            pagerank[i] = sum;
        }
        printf("%f\n", delta);
        if (delta <= 1e-6) {
            break;
        }
    }

    sort(0, url_number - 1, NULL, compare, swap);

    f = open_file("result.txt", "w");
    for (int i = 0; i < 10; ++i) {
        fprintf(f, "%s %.15f\n", idx2string[i], pagerank[i]);
    }
    fprintf(f, "%.2fs " SIZE_TYPE_BIG_FORMAT "K", clock_duration(),
            mp_get_length() / 1024);
    fclose(f);
}