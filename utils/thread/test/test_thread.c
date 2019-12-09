#include "../../print/print.h"
#include "../thread.h"

int counter = 0;

int generator() {
    int value = -1;

    if (counter < 20) {
        value = counter++;
    }

    return value;
}

int  res[50] = {};
int  pos = 0;
void write(int number) { res[pos++] = number; }

void *task(void *args) {
    thread_pool *tp = args;

    for (;;) {
        tp_lock(tp, 0);
        int number = generator();
        tp_unlock(tp, 0);

        tp_lock(tp, 1);
        write(number);
        tp_unlock(tp, 1);

        if (number == -1) {
            return NULL;
        }
    }
    return NULL;
}

int main() {
    boolean pass = T;
    mp_init(1 << 16, mp_exit);
    thread_pool *tp = tp_new(3, 2, task);
    tp_wait(tp);

    int got = generator(tp);
    if (got != -1) {
        print_err("generator should be -1, but got %d\n", got);
        pass = F;
    }
    for (int i = 0; i < 20; ++i) {
        if (i != res[i]) {
            print_err("res[%d] excepted %d, got %d\n", i, i, res[i]);
            pass = F;
        }
    }
    if (pass) {
        print_ok("All test case passed!\n");
    }
    return 0;
}