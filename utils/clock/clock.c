#include "clock.h"

time_t clock_start_time;

void   clock_start() { clock_start_time = clock(); }
double clock_duration() {
    return (double)(clock() - clock_start_time) / CLOCKS_PER_SEC;
}
