#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>

int find(const char line[5000], int len) {
    int set[150];

    for (int i = len - 1; i < 5000; ++i) {
        memset(set, 0, sizeof set);
        int good = 1;
        for (int j = 0; j < len; ++j) {
            char c = line[i-j];
            if(set[c]) {
                good = 0;
                break;
            }
            set[c] = 1;
        }
        if (good) {
            return i + 1;
        }
    }
}

void sol6() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input6.txt";
    FILE* file = fopen(fileName, "r");

    char line[5000];
    fgets(line, 5000, file);

    printf("Part 1: %d\n", find(line, 4));
    printf("Part 2: %d\n", find(line, 14));

    fclose(file);
}