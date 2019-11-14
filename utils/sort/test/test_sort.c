#include "../../boolean/boolean.h"
#include "../../print/print.h"
#include "../sort.h"
#include <assert.h>
#include <stdio.h>

int compare_int(void *args, int i, int j) {
    int *args_nums = (int *)args;

    return args_nums[i] - args_nums[j];
}
void swap_int(void *args, int i, int j) {
    int *args_nums = (int *)args;

    int temp = args_nums[i];
    args_nums[i] = args_nums[j];
    args_nums[j] = temp;
}

boolean test_int() {
    boolean pass = T;
    int     nums[7] = {5, 1, 4, 2, 7, 3, 6};

    sort(0, 6, nums, compare_int, swap_int);
    for (int i = 0; i < 7; i++) {
        if (nums[i] != i + 1) {
            print_err("Error at a[%d]=%d want %d\n", i, nums[i], i + 1);
            pass = F;
        }
    }
    return pass;
}

int compare_pair(void *args, int i, int j) {
    int *args_values = (int *)(args + 1);

    return args_values[i] - args_values[j];
}
void swap_pair(void *args, int i, int j) {
    char *args_keys = (char *)(args);
    int * args_values = (int *)(args + 1);

    char temp_key = args_keys[i];
    args_keys[i] = args_keys[j];
    args_keys[j] = temp_key;

    char temp_value = args_values[i];
    args_values[i] = args_values[j];
    args_values[j] = temp_value;
}

boolean pair() {
    boolean pass = T;
    char    keys[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int     values[7] = {5, 1, 4, 2, 7, 3, 6};
    void *  args[] = {keys, values};

    char want[7] = {'b', 'd', 'f', 'c', 'a', 'g', 'e'};

    sort(0, 6, args, compare_int, swap_int);
    for (int i = 0; i < 7; i++) {
        if (keys[i] != want[i] || values[i] != i + 1) {
            print_err("Error at %d(%c,%d) want %c\n", i, keys[i], values[i],
                      want[i]);
            pass = F;
        }
    }
    return pass;
}

int main() {
    boolean pass = T;

    pass &= test_int();

    if (pass) {
        print_ok("All testcases passed\n");
    } else {
        print_err("Some errors!\n");
    }
}