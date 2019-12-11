#include "../http.h"

int main() {
    char *rep = malloc(10000);
    get_page("8.8.8.8", 80, rep, 10000);
    printf("%s", rep);
    return 0;
}