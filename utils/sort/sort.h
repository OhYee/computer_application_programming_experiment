typedef int (*sort_compare_function)(void *, int, int);
typedef void (*sort_swap_function)(void *, int, int);

void sort(int l, int r, void *args, sort_compare_function compare,
          sort_swap_function swap);