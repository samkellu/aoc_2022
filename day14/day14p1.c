#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char buf[512];
    FILE* fp = fopen("day14.in", "r");

    int** walls = malloc(0);
    int** map;
    int num_walls, maxx, maxy;
    num_walls = maxx = maxy = 0;
    int minx = -1;
    int miny = -1;
    char* tok;

    while (fgets(buf, 512, fp)) {

        int prev_exists = 0;
        int prev[2];
        int cur[2];
        char* b = strdup(buf);
        char* b_mem = b;
        while ((tok = strsep(&b, " ")) != NULL) {

            if (strcmp(tok, "->") == 0) {
                continue;
            }
            walls = realloc(walls, sizeof(int*)* ++num_walls);
            walls[num_walls-1] = malloc(sizeof(int)*2);
            
            char* sub = strdup(tok);
            char* sub_mem = sub;
            walls[num_walls-1][0] = atoi(strsep(&sub, ","));
            maxx = walls[num_walls-1][0] > maxx ? walls[num_walls-1][0] : maxx;
            minx = walls[num_walls-1][0] < minx || minx == -1 ? walls[num_walls-1][0] : minx;
            
            walls[num_walls-1][1] = atoi(strsep(&sub, ","));
            maxy = walls[num_walls-1][1] > maxy ? walls[num_walls-1][1] : maxy;
            miny = walls[num_walls-1][1] < miny || minx == -1 ? walls[num_walls-1][1] : miny;    
            free(sub_mem);
            free(sub);
            cur[0] = walls[num_walls-1][0];
            cur[1] = walls[num_walls-1][1];

            if (prev_exists) {

                if (walls[num_walls-1][0] == prev[0]) {
                    int inc = walls[num_walls-1][1] > prev[1] ? -1 : 1;
                    int n1 = walls[num_walls-1][1];
                    int n2 = prev[1];
                    for (int j = n1 + inc; j != n2; j += inc) {
                        walls = realloc(walls, sizeof(int*)* ++num_walls);
                        walls[num_walls-1] = malloc(sizeof(int)*2);
                        walls[num_walls-1][0] = walls[num_walls-2][0];
                        walls[num_walls-1][1] = j;
                    }
                }
                if (walls[num_walls-1][1] == prev[1]) {
                    int inc = walls[num_walls-1][0] > prev[0] ? -1 : 1;
                    int n1 = walls[num_walls-1][0];
                    int n2 = prev[0];
                    printf("%d %d %d %d\n", walls[num_walls-1][0], walls[num_walls-1][1], n1, n2);
                    for (int j = n1 + inc; j != n2; j += inc) {
                        walls = realloc(walls, sizeof(int*)* ++num_walls);
                        walls[num_walls-1] = malloc(sizeof(int)*2);
                        walls[num_walls-1][0] = j;
                        walls[num_walls-1][1] = walls[num_walls-2][1];
                    }
                }
            }
            prev_exists = 1;
            prev[0] = cur[0];
            prev[1] = cur[1];
        }  
        free(b_mem);
    }
    maxx++;
    maxy++;
    map = calloc(maxx, sizeof(int*));
    for (int i = 0; i < maxx; i++) {
        map[i] = calloc(maxy, sizeof(int));
    }
    for (int i = 0; i < num_walls; i++) {
        printf("\n%d %d %d %d", walls[i][0],walls[i][1],maxx,maxy);
        map[walls[i][0]][walls[i][1]] = 1;
    }

    int at_rest = 1;
    int sand[2];
    int ind = 0;

    while (1) {
        if (at_rest) {
            at_rest = 0;
            sand[0] = 500;
            sand[1] = 0;
        } else {

            if (sand[1] == maxy-1) {
                printf("Number of units of sand: %d\n", ind);
                goto BREAK;
            }
            if (map[sand[0]][sand[1]+1] != 1) {
                sand[1]++;
            } else if (sand[0]-1 > 0 && map[sand[0]-1][sand[1]+1] != 1) {
                sand[1]++;
                sand[0]--;
            } else if (sand[0]+1 < maxx && map[sand[0]+1][sand[1]+1] != 1) {
                sand[1]++;
                sand[0]++;
            } else {
                map[sand[0]][sand[1]] = 1;
                at_rest = 1;
                ind++;
            }
        }

        printf("\n---------------------- %d ----------------------------\n", sand[1]);
        for (int j = -10; j < 10; j++) {
            for (int i = -25; i < 25; i++) {
                if (i == 0 && j == 0) {
                    printf("#");
                    continue;
                }
                if (sand[1]+j < 0 || sand[1]+j >= maxy) {
                    printf(" ");
                    continue;
                }
                if (sand[0]+i < 0 || sand[0]+i >= maxx) {
                    printf(" ");
                    goto NEXT;
                }
                if (map[sand[0]+i][sand[1]+j] == 0) {
                    printf(" ");
                    continue;
                }
                printf("%d", map[sand[0]+i][sand[1]+j]);
            }
            NEXT:
            printf("\n");
        }
        // usleep(50000);
    }
    BREAK:

    for (int i = 0; i < maxx; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < num_walls; i++) {
        free(walls[i]);
    }
    free(walls);
    fclose(fp);
}