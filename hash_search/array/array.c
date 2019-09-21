#include "../../utils/boolean/boolean.h"
#include "../../utils/compare/compare.h"
#include <stdio.h>

FILE *open_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == 0) {
        printf("Error: Can not open file %s.", filename);
        exit(1);
    }
    return f;
}

int main() {
    int       pattern_num = 0;
    const int maxm = 100;
    const int maxn = 100005;
    // char      patterns[1270688][maxn];
    char **patterns = malloc(sizeof(char *) * maxn);
    for (int i = 0; i < maxn; ++i) {
        patterns[i] = malloc(sizeof(char) * maxm);
    }
    FILE *f = open_file("../testcase/patterns.txt");
    while (~fscanf(f, "%s", patterns[pattern_num++]))
        ;
    --pattern_num;
    fclose(f);

    char word[maxn];
    f = open_file("../testcase/words.txt");
    while (~fscanf(f, "%s", word)) {
        int exists = 0;
        for (int i = 0; i < pattern_num; ++i) {
            exists |= compare_string(word, patterns[i]);
            if (exists)
                break;
        }
        printf("%s %s\n", word, exists ? "yes" : "no");
    }
    fclose(f);

    return 0;
}