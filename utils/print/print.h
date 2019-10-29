#pragma once
enum color { BLACK, RED, GREEN, YELLOW, BLUE, PINK, SKY, WHITE };

int print(int c, char *fmt, ...);
int print_err(char *fmt, ...);
int print_ok(char *fmt, ...);