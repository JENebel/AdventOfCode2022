#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int width8, height8 = 0;

bool is_visible_fos(int forest[width8][height8], int x, int y) {
    int h = forest[x][y];

    //from right
    bool vis = true;
    for (int i = x + 1; i < width8; ++i)
        if(forest[i][y] >= h) vis = false;
    if(vis) return true;

    //from left
    vis = true;
    for (int i = x - 1; i >= 0; --i)
        if(forest[i][y] >= h) vis = false;
    if(vis) return true;

    //from bottom
    vis = true;
    for (int i = y + 1; i < height8; ++i)
        if(forest[x][i] >= h) vis = false;
    if(vis) return true;

    //from top
    vis = true;
    for (int i = y - 1; i >= 0; --i)
        if(forest[x][i] >= h) vis = false;
    if(vis) return true;

    return false;
}

int scenic_score(int forest[width8][height8], int x, int y) {
    int h = forest[x][y];
    int trees = 0;
    int score;
    //left
    for (int i = x + 1; i < width8; ++i) {
        trees++;
        if(forest[i][y] >= h) break;
    }
    score = trees;
    trees = 0;
    //right
    for (int i = x - 1; i >= 0; --i) {
        trees++;
        if(forest[i][y] >= h) break;
    }
    score *= trees;
    trees = 0;
    //down
    for (int i = y + 1; i < height8; ++i) {
        trees++;
        if(forest[x][i] >= h) break;
    }
    score *= trees;
    trees = 0;
    //up
    for (int i = y - 1; i >= 0; --i) {
        trees++;
        if(forest[x][i] >= h) break;
    }
    score *= trees;
    return score;
}

void sol8() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input8.txt";
    FILE* file = fopen(fileName, "r");

    char line[120];

    height8 = 0;
    //Get size
    while(fgets(line, 120, file)) {
        width8 = (int)strlen(line);
        height8 += 1;
    }

    //Load data
    int forest[width8][height8];
    fclose(file);
    file = fopen(fileName, "r");
    for (int i = 0; i < height8; ++i) {
        fgets(line, 120, file);
        for (int j = 0; j < width8; ++j) {
            forest[j][i] = line[j] - 48;
        }
    }

    //Solve
    int visible = 0;
    int best = 0;
    for (int y = 0; y < height8; ++y) {
        for (int x = 0; x < width8; ++x) {
            int score = scenic_score(forest, x, y);
            if (score > best) best = score;

            if(is_visible_fos(forest, x, y)) {
                visible++;
                //printf("%d", forest[x][y]);
            } //else printf(".");
        }
//        printf("\n");
    }

    printf("Part 1: %d\n", visible);
    printf("Part 2: %d\n", best);

    fclose(file);
}