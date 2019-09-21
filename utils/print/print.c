#include "print.h"
#include <stdarg.h>
#include <stdio.h>

void begin(int c) {
    switch (c) {
        case BLACK:
            printf("\033[1;30m");
            break;
        case RED:
            printf("\033[1;31m");
            break;
        case GREEN:
            printf("\033[1;32m");
            break;
        case YELLOW:
            printf("\033[1;33m");
            break;
        case BLUE:
            printf("\033[1;34m");
            break;
        case PINK:
            printf("\033[1;35m");
            break;
        case SKY:
            printf("\033[1;36m");
            break;
        case WHITE:
            printf("\033[1;37m");
            break;
    }
}
void end() { printf("\033[0m"); }

int print(int c, char *fmt, ...) {
    va_list args; //定义一个va_list类型的变量，用来储存单个参数
    va_start(args, fmt); //使args指向可变参数的第一个参数
    begin(c);
    int ret = vprintf(fmt, args); //必须用vprintf等带V的
    end();
    va_end(args); //结束可变参数的获取
    return ret;
}

int print_err(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    begin(RED);
    int ret = vfprintf(stdout, fmt, args);
    end();
    va_end(args);
    return ret;
}
int print_ok(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    begin(GREEN);
    int ret = vfprintf(stdout, fmt, args);
    end();
    va_end(args);
    return ret;
}
