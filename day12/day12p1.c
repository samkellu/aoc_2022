#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_path(char** map, int cur[2]) {

    printf("call\n");
    if (map[cur[0]][cur[1]] == 'E') {
        printf("done");
    }

    int next[2];

    if (map[cur[0]][cur[1]+1] == map[cur[0]][cur[1]] + 1 || map[cur[0]][cur[1]+1] == map[cur[0]][cur[1]]
         || map[cur[0]][cur[1]+1] == map[cur[0]][cur[1]] - 1 || map[cur[0]][cur[1]+1] == 'E') {

        next[0] = cur[0];
        next[1] = cur[1]+1;
        find_path(map, next);
    }
    if (map[cur[0]][cur[1]-1] == map[cur[0]][cur[1]] + 1 || map[cur[0]][cur[1]-1] == map[cur[0]][cur[1]]
         || map[cur[0]][cur[1]-1] == map[cur[0]][cur[1]] - 1 || map[cur[0]][cur[1]-1] == 'E') {

        next[0] = cur[0];
        next[1] = cur[1]-1;
        find_path(map, next);
            
    }
    if (map[cur[0]+1][cur[1]] == map[cur[0]][cur[1]] + 1 || map[cur[0]+1][cur[1]] == map[cur[0]][cur[1]]
         || map[cur[0]+1][cur[1]] == map[cur[0]][cur[1]] - 1 || map[cur[0]+1][cur[1]] == 'E') {

        next[0] = cur[0]+1;
        next[1] = cur[1];
        find_path(map, next);
    }
    if (map[cur[0]-1][cur[1]] == map[cur[0]][cur[1]] + 1 || map[cur[0]-1][cur[1]] == map[cur[0]][cur[1]]
         || map[cur[0]-1][cur[1]] == map[cur[0]][cur[1]] - 1 || map[cur[0]-1][cur[1]] == 'E') {

        next[0] = cur[0]-1;
        next[1] = cur[1];
        find_path(map, next);
    }
}

int main() {

    FILE* fp = fopen("day12.in", "r");
    char buf[512];

    char** map = malloc(0);
    int num_lines = 0;

    while (fgets(buf, 512, fp)) {
        map = realloc(map, sizeof(char*) * ++num_lines);
        map[num_lines-1] = malloc(sizeof(char) * strlen(buf));
        memcpy(map[num_lines-1], buf, strlen(buf));
    }

    int start[2];
    int end[2];

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < strlen(map[i]); j++) {
            if (map[i][j] == 'S') {
                start[0] = i;
                start[1] = j;
            } else if (map[i][j] == 'E') {
                end[0] = i;
                end[1] = j;
            }
        }
    }

    find_path(map,start);

    free(map);
    fclose(fp);
    return 1;
}