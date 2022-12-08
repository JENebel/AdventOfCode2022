#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>

#define SIZE 50

int read_int(FILE* file) {
    int i = 0;
    while (1) {
        int c = fgetc(file);
        if (isdigit(c)) {
            i *= 10;
            i += c - 48;
        } else {
            return i;
        }
    }
}

void sol5() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input5.txt";
    FILE* file = fopen(fileName, "r");

    //Part1
    char stacks[SIZE][SIZE];
    int  heights[SIZE];
    memset(heights, 0, sizeof heights);

    char line[100];

    //Load stacks
    while (fgets(line, sizeof(line), file)) {
        if(line[0] == '\n') break;

        for (int i = 0; i < SIZE; ++i) {
            if(line[i] == '\n') break;

            if(isalpha(line[i])) {
                int index = (i - 1) / 4;
                stacks[index][heights[index]] = line[i];
                heights[index]++;
            }
        }
    }

    //Invert stacks
    for (int i = 0; i < SIZE; ++i) {
        int h = heights[i];
        for (int j = 0; j < h / 2; ++j) {
            char temp = stacks[i][h-j-1];
            stacks[i][h-j-1] = stacks[i][j];
            stacks[i][j] = temp;
        }
    }

    char stacks2[SIZE][SIZE];
    int  heights2[SIZE];
    memcpy(stacks2, stacks, sizeof stacks);
    memcpy(heights2, heights, sizeof heights);

    /*for (int i = 0; i < SIZE; ++i) {
        int h = heights2[i];
        if(h == 0) break;
        for (int j = 0; j < h; ++j) {
            printf("%c", stacks2[i][j]);
        }
        printf("\n");
    }*/

    while(1) {
        int c = fgetc(file);
        if(c == -1) break;
        for (int i = 0; i < 4; ++i) { fgetc(file); }
        int cnt = read_int(file);
        for (int i = 0; i < 5; ++i) { fgetc(file); }
        int from = read_int(file) - 1;
        for (int i = 0; i < 3; ++i) { fgetc(file); }
        int to = read_int(file) - 1;

        for (int i = 0; i < cnt; ++i) {
            heights[from]--;
            stacks[to][heights[to]] = stacks[from][heights[from]];
            heights[to]++;
        }

        for (int i = 0; i < cnt; ++i) {
            stacks2[to][heights2[to] + i] = stacks2[from][heights2[from] - cnt + i];
        }
        heights2[from] -= cnt;
        heights2[to] += cnt;
    }

    printf("Part 1: ");
    for (int i = 0; i < SIZE; ++i) {
        if(heights[i]) {
            printf("%c", stacks[i][heights[i] - 1]);
        }
    }

    printf("\nPart 2: ");
    for (int i = 0; i < SIZE; ++i) {
        if(heights2[i]) {
            printf("%c", stacks2[i][heights2[i] - 1]);
        }
    }

    fclose(file);
}