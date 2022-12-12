#include <stdio.h>

int contains(char string[100], int sfrom, int sto, char c) {
    for (int i = sfrom; i < sto; ++i) {
        if (string[i] == c) {
            return 1;
        }
    }
    return 0;
}

int length(char line[100]) {
    int length = 0;
    for (int i = 0; i < 100; ++i) {
        if(line[i] != '\0')
            length++;
        else
            break;
    }
    return length;
}

char shared_item(char first[100], int ffrom, int fto, char second[100], int sfrom, int sto) {
    for (int i = ffrom; i < fto; ++i) {
        if (contains(second, sfrom, sto, first[i])) {
            return first[i];
        }
    }
    return '\0';
}

char triple_shared(char first[100], char second[100], char third[100]) {
    for (int i = 0; i < length(first); ++i) {
        for (int j = 0; j < length(second); ++j) {
            for (int k = 0; k < length(third); ++k) {
                if(first[i] == second[j] && first[i] == third[k]) {
                    return first[i];
                }
            }
        }
    }
    return '\0';
}

int prio(char c) {
    if (c<=90)
        return c - 38;
    else
        return c - 96;
}

void sol3() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input3.txt";
    FILE* file = fopen(fileName, "r");
    char line[100];

    //Part1
    int sum = 0;
    while (fgets(line, sizeof(line), file)) {
        char shared = shared_item(line, 0, length(line)/2, line, length(line)/2, length(line));
        sum += prio(shared);
    }
    printf("part 1: %d\n", sum);

    //Part2
    file = fopen(fileName, "r");
    sum = 0;
    while (fgets(line, sizeof(line), file)) {
        char line2[100];
        char line3[100];
        fgets(line2, sizeof(line), file);
        fgets(line3, sizeof(line), file);

        char shared = triple_shared(line, line2, line3);
        sum += prio(shared);
    }
    printf("part 2: %d\n", sum);


    fclose(file);
}