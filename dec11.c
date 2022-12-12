#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


struct Monkey {
    int item_cnt;
    unsigned long long items[50];
    char operator;
    int op_val;
    int divisor;
    int case_f, case_t;
    int inspections;
};

struct Monkey* monkeys[50];
int monkey_cnt = 0;

void sol11() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input11.txt";
    FILE* file = fopen(fileName, "r");

    char line[120];

    memset(monkeys, 0, sizeof(monkeys));

    int prod = 1;

    //Load in
    while(fgets(line, 120, file)) {
        struct Monkey* monkey = malloc(sizeof(struct Monkey));
        memset(monkey, 0, sizeof(struct Monkey));

        fgets(line, 120, file);
        int beginning = 18;
        int i = 18;
        while (true) {
            if(!isdigit(line[i])) {
                char num_str[120];
                strcpy(num_str, &line[beginning]);
                num_str[i] = '\0';
                int item = atoi(num_str);
                i++;
                beginning = i;
                monkey->items[monkey->item_cnt] = item;
                if (!item) break;
                monkey->item_cnt++;
            }
            i++;
        }
        fgets(line, 120, file);
        monkey->operator = line[23];
        if(line[25] == 'o') monkey->operator = '^';
        else monkey->op_val = atoi(&line[25]);
        fgets(line, 120, file);
        monkey->divisor = atoi(&line[21]);
        prod *= monkey->divisor;
        fgets(line, 120, file);
        monkey->case_t = atoi(&line[29]);
        fgets(line, 120, file);
        monkey->case_f = atoi(&line[30]);
        fgets(line, 120, file);

        monkeys[monkey_cnt] = monkey;
        monkey_cnt++;
    }

    //Do 20 rounds
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < monkey_cnt; ++j) {
            struct Monkey* monkey = monkeys[j];
            int count = monkey->item_cnt;
            monkey->item_cnt = 0;
            for (int k = 0; k < count; ++k) {
                unsigned long long item = monkey->items[k];

                switch (monkey->operator) {
                    case '+': {
                        item += monkey->op_val;
                        break;
                    }
                    case '*': {
                        item *= monkey->op_val;
                        break;
                    }
                    case '^': {
                        item *= item;
                        break;
                    }
                    default: break;
                }

                item %= prod;
                //item /= 3;

                struct Monkey* recipient = monkeys[monkey->case_f];
                if (item % monkey->divisor == 0) {
                    recipient = monkeys[monkey->case_t];
                }

                recipient->items[recipient->item_cnt] = item;
                recipient->item_cnt++;
                monkey->inspections++;
            }
        }
    }

    unsigned long long best = 0;
    unsigned long long second = 0;
    for (int i = 0; i < monkey_cnt; ++i) {
        printf("Monkey %d: %d\n", i, monkeys[i]->inspections);
        if (monkeys[i]->inspections > best) {
            second = best;
            best = monkeys[i]->inspections;
        } else if (monkeys[i]->inspections > second) {
            second = monkeys[i]->inspections;
        }
    }

    printf("%llu\n", best * second);

    fclose(file);
}