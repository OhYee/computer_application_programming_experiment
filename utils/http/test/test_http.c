#include "../http.h"

int main() {
    char *rep = malloc(10000);
    get_page("39.156.69.79", 80, rep, 10000);
    printf("%s", rep);
    return 0;
}