#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_SIZE 2048

int main() {

    int** map = malloc(START_SIZE*sizeof(int*));
    for (int i = 0; i < START_SIZE; i++) {
        map[i] = calloc(START_SIZE, sizeof(int));
    }

    int rope[10][2];

    for (int i = 0; i < 10; i++) {
        rope[i][0] = 1024;
        rope[i][1] = 1024;
    }

    char buf[32];
    FILE* fp = fopen("day9.in", "r");

    while (fgets(buf, 32, fp)) {
        char* iterations = strtok(buf, " ");
        iterations = strtok(NULL, " ");

        for (int u = 0; u < atoi(iterations); u++) {
            if (buf[0] == 'L') {
                rope[0][0]--;
            } else if (buf[0] == 'R') {
                rope[0][0]++;
            } else if (buf[0] == 'U') {
                rope[0][1]--;
            } else if (buf[0] == 'D') {
                rope[0][1]++;
            }

            for (int i = 1; i < 10; i++) {
                if (abs(rope[i-1][0] - rope[i][0]) > 1 && abs(rope[i-1][1] - rope[i][1]) <= 1) {
                    rope[i][0] = rope[i-1][0] - rope[i][0] > 0 ? rope[i-1][0]-1 : rope[i-1][0]+1;
                    rope[i][1] = rope[i-1][1];
                }
                if (abs(rope[i-1][0] - rope[i][0]) > 1 && abs(rope[i-1][1] - rope[i][1]) > 1) {
                    rope[i][0] = rope[i-1][0] - rope[i][0] > 0 ? rope[i-1][0]-1 : rope[i-1][0]+1;
                    rope[i][1] = rope[i-1][1] - rope[i][1] > 0 ? rope[i-1][1]-1 : rope[i-1][1]+1;
                }
                if (abs(rope[i-1][1] - rope[i][1]) > 1 && abs(rope[i-1][0] - rope[i][0]) <= 1) {
                    rope[i][1] = rope[i-1][1] - rope[i][1] > 0 ? rope[i-1][1]-1 : rope[i-1][1]+1;
                    rope[i][0] = rope[i-1][0];
                }
                if (abs(rope[i-1][1] - rope[i][1]) > 1 && abs(rope[i-1][0] - rope[i][0]) > 1) {
                    rope[i][1] = rope[i-1][1] - rope[i][1] > 0 ? rope[i-1][1]-1 : rope[i-1][1]+1;
                    rope[i][0] = rope[i-1][0] - rope[i][0] > 0 ? rope[i-1][0]-1 : rope[i-1][0]+1;
                }
            }
            int** tmap = malloc(10*sizeof(int*));
            for (int i = 0; i < 10; i++) {
                tmap[i] = malloc(10*sizeof(int));
                for (int j = 0; j < 10; j++) {
                    tmap[i][j] = -1;
                }
            }

            int max_l, max_r;
            max_l = max_r = 0;

            for (int i = 0; i < 10; i++) {
                if (rope[i][0] > max_r) {
                    max_r = rope[i][0];
                }
                if (rope[i][1] > max_l) {
                    max_l = rope[i][1];
                }
            }

            for (int i = 0; i < 10; i++) {
                tmap[rope[i][0]-(max_r-9)][rope[i][1]-(max_l-9)] = i;
            }

            printf("%s %d: %d\n", buf, atoi(iterations), u);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (tmap[j][i] == -1) {
                        printf("-");
                        continue;
                    }
                    printf("%d", tmap[j][i]);
                }
                printf("\n");
            }
            for (int i = 0; i < 10; i++) {
                free(tmap[i]);
            }
            free(tmap);
            map[rope[9][0]][rope[9][1]] = 1;
        }
    }

    int count = 0;

    for (int i = 0; i < START_SIZE; i++) {
        for (int j = 0; j < START_SIZE; j++) {
            if (map[i][j] == 1) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    
    for (int i = 0; i < START_SIZE; i++) {
        free(map[i]);
    }
    free(map);
    fclose(fp);
}