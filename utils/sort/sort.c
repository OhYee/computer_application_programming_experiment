#include "sort.h"

void sort(int l, int r, void *args, sort_compare_function compare,
          sort_swap_function swap) {
    if (l < r) {
        int left = l;
        int right = r;
        int mid = l;

        int a = compare(args, l, r), b = compare(args, l, (l + r) / 2),
            c = compare(args, (l + r) / 2, r);
        if (a == b && b == c) {
            mid = (l + r) / 2;
        } else if (a == c) {
            mid = l;
        } else {
            mid = r;
        }

        while (left < right) {
            while (left < right && mid < right &&
                   compare(args, mid, right) < 0) {
                right--;
            }
            if (left < right && mid < right) {
                swap(args, left++, right);
                mid = right;
            }
            while (left < right && left < mid && compare(args, left, mid) < 0) {
                left++;
            }
            if (left < right && left < mid) {
                swap(args, left, right--);
                mid = left;
            }
        }
        // swap(left, mid);

        // 递归调用
        sort(l, mid - 1, args, compare, swap); // 排序mid左边
        sort(mid + 1, r, args, compare, swap); // 排序mid右边
    }
}