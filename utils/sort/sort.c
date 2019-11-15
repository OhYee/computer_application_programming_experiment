#include "sort.h"

void sort(int l, int r, void *args, sort_compare_function compare,
          sort_swap_function swap) {
    if (l < r) {
        int left = l;
        int right = r;
        int mid = l;
        while (left < right) {
            while (left < right && compare(args, right, mid) >= 0) {
                right--;
            }
            if (left < right) {
                swap(args, left++, right);
                mid = right;
            }
            while (left < right && compare(args, left, mid) < 0) {
                left++;
            }
            if (left < right) {
                swap(args, right--, left);
                mid = left;
            }
        }
        // swap(left, mid);

        // 递归调用
        sort(l, mid - 1, args, compare, swap); // 排序mid左边
        sort(mid + 1, r, args, compare, swap); // 排序mid右边
    }
}