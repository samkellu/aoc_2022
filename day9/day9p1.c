#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_SIZE 1024

int main() {

    char** map = malloc(START_SIZE*sizeof(char*));
    for (int i = 0; i < START_SIZE; i++) {
        map[i] = malloc(START_SIZE*sizeof(char));
        for (int j = 0; j < START_SIZE; j++) {
            map[i][j] = '\0';
        }
    }

    int hx = 512;
    int hy = 512;
    int tx = 512;
    int ty = 512;

    char buf[32];
    FILE* fp = fopen("day9.in", "r");

    while (fgets(buf, 32, fp)) {
        char* iterations = strtok(buf, " ");
        iterations = strtok(NULL, " ");

        if (buf[0] == 'L') {
            for (int i = 0; i < atoi(iterations); i++) {
                hx--;
                printf("%d %d\n", abs(hx - tx), abs(hy - ty));
                if (abs(hx - tx) > 1) {
                    tx--;
                    if (hy != ty) {
                        ty = hy;
                    }
                }
                map[tx][ty] = 1;
            }

        } else if (buf[0] == 'U') {
            for (int i = 0; i < atoi(iterations); i++) {
                hy++;
                if (abs(hy - ty) > 1) {
                    ty++;
                    if (hx != tx) {
                        tx = hx;
                    }
                }
                map[tx][ty] = 1;
            }

        } else if (buf[0] == 'R') {
            for (int i = 0; i < atoi(iterations); i++) {
                hx++;
                if (abs(hx - tx) > 1) {
                    tx++;
                    if (hy != ty) {
                        ty = hy;
                    }
                }
                map[tx][ty] = 1;
            }

        } else if (buf[0] == 'D') {
            for (int i = 0; i < atoi(iterations); i++) {
                hy--;
                if (abs(hy - ty) > 1) {
                    ty--;
                    if (hx != tx) {
                        tx = hx;
                    }
                }
                map[tx][ty] = 1;
            }
        } 
    }

    int count = 1;

    for (int i = 0; i < START_SIZE; i++) {
        for (int j = 0; j < START_SIZE; j++) {
            count = map[i][j] == 1 ? count + 1 : count;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < START_SIZE; i++) {
        free(map[i]);
    }
    free(map);
    fclose(fp);
}