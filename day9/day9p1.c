#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_SIZE 1024

int main() {

    int** map = malloc(START_SIZE*sizeof(int*));
    for (int i = 0; i < START_SIZE; i++) {
        map[i] = calloc(START_SIZE, sizeof(int));
    }
    map[512][512] = 1;

    int hx = 512;
    int hy = 512;
    int tx = 512;
    int ty = 512;

    char buf[32];
    FILE* fp = fopen("day9.in", "r");

    while (fgets(buf, 32, fp)) {
        char* iterations = strtok(buf, " ");
        iterations = strtok(NULL, " ");

        for (int i = 0; i < atoi(iterations); i++) {
            if (buf[0] == 'L') {
                hx--;
                if (abs(hx - tx) > 1) {
                    tx--;
                    if (hy != ty) {
                        ty = hy;
                    }
                }

            } else if (buf[0] == 'R') {
                hx++;
                if (abs(hx - tx) > 1) {
                    tx++;
                    if (hy != ty) {
                        ty = hy;
                    }
                }

            } else if (buf[0] == 'U') {
                hy++;
                if (abs(hy - ty) > 1) {
                    ty++;
                    if (hx != tx) {
                        tx = hx;
                    }
                }

            } else if (buf[0] == 'D') {
                hy--;
                if (abs(hy - ty) > 1) {
                    ty--;
                    if (hx != tx) {
                        tx = hx;
                    }
                }
            }
            map[tx][ty] = 1;
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