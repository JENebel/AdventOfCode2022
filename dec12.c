#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool can_move(int part, int curr_ele, int target_ele) {
    if (part == 1) return target_ele <= curr_ele + 1;
    else return target_ele >= curr_ele - 1;
}

int solve(int part) {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input12.txt";
    FILE* file = fopen(fileName, "r");

    char line[120];

    int end_x = 0, end_y = 0;
    int start_x = 0, start_y = 0;
    int width, height = 0;

    //Load size
    while(fgets(line, 120, file)) {
        width = (int)strlen(line);
        height += 1;
    }

    int map[width][height];

    //Load map
    file = fopen(fileName, "r");
    for (int y = 0; y < height; ++y) {
        fgets(line, 120, file);
        for (int x = 0; x < width; ++x) {
            //start & end
            if (line[x] == 'S') {
                start_x = x;
                start_y = y;
                map[x][y] = 'a';
                continue;
            }
            if (line[x] == 'E') {
                end_x = x;
                end_y = y;
                map[x][y] = 'z';
                continue;
            }

            //Regular tile
            map[x][y] = (int)line[x];
        }
    }

    int dists[width][height];
    memset(dists, -1 , sizeof(dists));

    if (part == 1) {
        dists[start_x][start_y] = 0;
    } else {
        dists[end_x][end_y] = 0;
    }

    //Breadth first
    int max_steps = 1000;
    for (int i = 0; i < max_steps; ++i) {
        //Expand all visited
        int new_dists[width][height];
        memcpy(new_dists, dists, sizeof(dists));

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (dists[x][y] == -1) continue;
                int curr_ele = map[x][y];

                if (part == 2 && curr_ele == 'a') {
                    return i;
                }

                //Right (x + 1)
                if (x + 1 < width && dists[x + 1][y] == -1 && can_move(part, curr_ele, map[x + 1][y])) {
                    new_dists[x + 1][y] = i + 1;
                }
                //Left (x - 1)
                if (x > 0 && dists[x - 1][y] == -1 && can_move(part, curr_ele, map[x - 1][y])) {
                    new_dists[x - 1][y] = i + 1;
                }
                //Down (y + 1)
                if (y + 1 < height && dists[x][y + 1] == -1 && can_move(part, curr_ele, map[x][y + 1])) {
                    new_dists[x][y + 1] = i + 1;
                }
                //Up (y - 1)
                if (y > 0 && dists[x][y - 1] == -1 && can_move(part, curr_ele, map[x][y - 1])) {
                    new_dists[x][y - 1] = i + 1;
                }
            }
        }

        memcpy(dists, new_dists, sizeof(new_dists));

        if (part == 1 && dists[end_x][end_y] != -1) {
            fclose(file);
            return dists[end_x][end_y];
        }
    }
}

void sol12() {
    printf("Part 1: %d\n", solve(1));
    printf("Part 2: %d\n", solve(2));
}