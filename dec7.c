#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dir {
    char name[50];
    struct Dir* parent;
    struct Dir* dirs[100];
    int dir_len;
    int file_size_sum;
};

int prefix(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int dir_siz(struct Dir* dir) {
    int sum = dir->file_size_sum;
    for (int i = 0; i < dir->dir_len; ++i) {
        sum += dir_siz(dir->dirs[i]);
    }
    return sum;
}

int sum_sub_100k(struct Dir* root) {
    int sum = 0;
    int loc = dir_siz(root);
    if(loc < 100000) sum += loc;

    for (int i = 0; i < root->dir_len; ++i) {
        sum += sum_sub_100k(root->dirs[i]);
    }

    return sum;
}

int smallest_ok(struct Dir* dir, int needed) {
    int best = dir_siz(dir);
    if(best < needed) best = 70000000;

    for (int i = 0; i < dir->dir_len; ++i) {
        int cont = smallest_ok(dir->dirs[i], needed);
        if(cont >= needed && cont < best) best = cont;
    }

    return best;
}

void sol7() {
    char const* const fileName = "C:\\Users\\Joachim\\CLionProjects\\AdventOfCode\\input7.txt";
    FILE* file = fopen(fileName, "r");

    struct Dir root;
    memset(&root, 0, (sizeof(struct Dir)));
    strcpy(root.name, "/");


    struct Dir* currDir = &root;

    char line[50];

    fgets(line, 50, file);

    while(fgets(line, 50, file)) {
        if(prefix("$ ls", line)) {
            while(fgets(line, 50, file) && !prefix("$", line)) {
                if(prefix("dir ", line)) {
                    struct Dir* new = malloc(sizeof(struct Dir));
                    memset(new, 0,(sizeof(struct Dir)));
                    strcpy(new->name, strtok(&line[4], "\n"));
                    new->parent = currDir;
                    currDir->dirs[currDir->dir_len] = new;
                    currDir->dir_len++;
                } else {
                    int size = 0;
                    for (int i = 0; i < 50; ++i) {
                        if(line[i] == ' ') break;
                        size = 10 * size;
                        size += line[i] - 48;
                    }
                    currDir->file_size_sum += size;
                }
            }
        }

        if (prefix("$ cd ..", line)) {
            currDir = currDir->parent;
        } else if (prefix("$ cd ", line)) {
            for (int i = 0; i < currDir->dir_len; ++i) {
                if(strcmp(currDir->dirs[i]->name, strtok(&line[5], "\n")) == 0) {
                    currDir = currDir->dirs[i];
                    break;
                }
            }
        }
    }

    printf("Part 1: %d\n", sum_sub_100k(&root));
    int needed = 30000000 - (70000000 - dir_siz(&root));
    printf("Part 2: %d", smallest_ok(&root, needed));

    fclose(file);
}