#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void sol12() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input12.txt";
    FILE* file = fopen(fileName, "r");

    char line[120];

    int end_x = 0, end_y = 0;
    int width, height = 0;

    //Load size
    while(fgets(line, 120, file)) {
        width = (int)strlen(line);
        height += 1;
    }

    int map[width][height];
    int dists[width][height];

    printf("%d by %d\n", width, height);

    //Load map
    file = fopen(fileName, "r");
    for (int y = 0; y < height; ++y) {
        fgets(line, 120, file);
        for (int x = 0; x < width; ++x) {
            dists[x][y] = -1;
            //start & end
            if (line[x] == 'S') {
                map[x][y] = 'a';
                dists[x][y] = 0;
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

                //Right (x + 1)
                if (x + 1 < width && dists[x + 1][y] == -1 && map[x + 1][y] <= curr_ele + 1) {
                    new_dists[x + 1][y] = i + 1;
                }
                //Left (x - 1)
                if (x > 0 && dists[x - 1][y] == -1 && map[x - 1][y] <= curr_ele + 1) {
                    new_dists[x - 1][y] = i + 1;
                }
                //Down (y + 1)
                if (y + 1 < height && dists[x][y + 1] == -1 && map[x][y + 1] <= curr_ele + 1) {
                    new_dists[x][y + 1] = i + 1;
                }
                //Up (y - 1)
                if (y > 0 && dists[x][y - 1] == -1 &&map[x][y - 1] <= curr_ele + 1) {
                    new_dists[x][y - 1] = i + 1;
                }
            }
        }

        memcpy(dists, new_dists, sizeof(new_dists));

        if (dists[end_x][end_y] != -1) {
            break;
        }
    }

    /*for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            printf(" %d ", dists[x][y]);
        }
        printf("\n");
    }*/

    printf("Part 1: %d\n", dists[end_x][end_y]);
    printf("Part 2: \n");

    fclose(file);
}