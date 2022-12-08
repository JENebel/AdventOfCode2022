#include <stdio.h>
#include <stdlib.h>

#define MAX_ELVES 3000

void sol1() {
    int elves[MAX_ELVES] = {0};
    int elf = 0;
    char line[10];
    while(1) {
        gets(line);
        if (line[0] == 0 || line[0] == 46) {
            elf++;
            if (line[0] == 46) {
                break;
            }
        } else {
            elves[elf] += atoi(line);
        }
    }

    int best = 0;
    int second = 0;
    int third = 0;

    for(int i = 0; i < MAX_ELVES; i++) {
        if(elves[i] > best) {
            third = second;
            second = best;
            best = elves[i];
        } else if(elves[i] > second) {
            third = second;
            second = elves[i];
        } else if(elves[i] > third) {
            third = elves[i];
        }
    }

    printf("%d", best+second+third);
}
