#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void sol4() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input4.txt";
    FILE* file = fopen(fileName, "r");
    char line[100];

    //Part1
    int p1_sum = 0;
    int p2_sum = 0;

    int secs[4];
    int done = 0;

    while (!done) {
        for (int i = 0; i < 4; ++i) {
            int temp = 0;
            while (1) {
                int c = fgetc(file);
                if (isdigit(c)) {
                    temp *= 10;
                    temp += c - 48;
                } else {
                    if (c == -1) done = 1;
                    break;
                }
            }
            secs[i] = temp;
        }

        //Calc this instance
        if(secs[0] >= secs[2] && secs[1] <= secs[3] || secs[2] >= secs[0] && secs[3] <= secs[1]) {
            p1_sum++;
        }
        if((secs[2] <= secs[1] && secs[3] >= secs[0]) || (secs[0] <= secs[3] && secs[1] >= secs[2])) {
            p2_sum++;
        }
    }

    printf("part 1: %d\n", p1_sum);
    printf("part 2: %d\n", p2_sum);


    fclose(file);
}