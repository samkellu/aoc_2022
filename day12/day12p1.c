#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 163
#define HEIGHT 41


int main() {

    FILE* fp = fopen("day12.in", "r");
    char buf[512];
    char map[HEIGHT][WIDTH];
    int num_lines = 0;

    while (fgets(buf, 512, fp)) {
        
        memcpy(map[num_lines++], buf, strlen(buf));
    }

    int** queue = malloc(sizeof(int*)*2);
    queue[0] = malloc(sizeof(int)*2);
    queue[1] = malloc(sizeof(int)*2);
    queue[1][0] = -1;
    int queue_size = 2;

    int end[2];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == 'S') {
                queue[0][0] = i;
                queue[0][1] = j;
                map[i][j] = 'a';
            }
            if (map[i][j] == 'E') {
                end[0] = i;
                end[1] = j;
                map[i][j] = 'z';
            }
        }
    }

    int vis[HEIGHT][WIDTH] = { 0 };
    int cursor = 0;
    int layer = 0;
    int valid_layer = 0;

    while (cursor < queue_size) {

        if (queue[cursor][0] == -1) {
            printf("layer %d\n", layer);
            free(queue[cursor]);
            cursor++;
            queue = realloc(queue, sizeof(int*) * ++queue_size);
            if (!valid_layer) {
                break;
            }
            queue[queue_size-1] = malloc(sizeof(int)*2);
            queue[queue_size-1][0] = -1;
            valid_layer = 0;
            layer++;
            continue;
        }

        int val = map[queue[cursor][0]][queue[cursor][1]];
        if (queue[cursor][0] == end[0] && queue[cursor][1] == end[1]) {
            printf("done %d\n\n\n\n", layer);
            break;
        }

        vis[queue[cursor][0]][queue[cursor][1]] = 1;

        int num_offset = 0;
        int** offset = malloc(0);

        if (queue[cursor][0] > 0) {
            offset = realloc(offset, sizeof(int*) * ++num_offset);
            offset[num_offset-1] = malloc(sizeof(int) * 2);
            offset[num_offset-1][0] = -1; 
            offset[num_offset-1][1] = 0; 
        }
        if (queue[cursor][0] + 1 < HEIGHT) {
            offset = realloc(offset, sizeof(int*) * ++num_offset);
            offset[num_offset-1] = malloc(sizeof(int) * 2);
            offset[num_offset-1][0] = 1; 
            offset[num_offset-1][1] = 0; 
        }
        if (queue[cursor][1] + 1 < WIDTH) {
            offset = realloc(offset, sizeof(int*) * ++num_offset);
            offset[num_offset-1] = malloc(sizeof(int) * 2);
            offset[num_offset-1][0] = 0; 
            offset[num_offset-1][1] = 1; 
        }
        if (queue[cursor][1] > 0) {
            offset = realloc(offset, sizeof(int*) * ++num_offset);
            offset[num_offset-1] = malloc(sizeof(int) * 2);
            offset[num_offset-1][0] = 0; 
            offset[num_offset-1][1] = -1; 
        }

        for (int i = 0; i < num_offset; i++) {
            if (vis[queue[cursor][0] + offset[i][0]][queue[cursor][1] + offset[i][1]] != 1 && 
               map[queue[cursor][0] + offset[i][0]][queue[cursor][1] + offset[i][1]] <= val + 1) {

                printf("%d %d\n", queue[cursor][0] + offset[i][0], queue[cursor][1] + offset[i][1]);
                for (int j = cursor+1; j < queue_size; j++) {
                    if (queue[cursor][0] == queue[j][0] && queue[cursor][1] == queue[j][1]) {
                        goto NEXT;
                    }
                }
                queue = realloc(queue, sizeof(int*) * ++queue_size);
                queue[queue_size-1] = malloc(sizeof(int)*2);
                queue[queue_size-1][0] = queue[cursor][0] + offset[i][0];
                queue[queue_size-1][1] = queue[cursor][1] + offset[i][1];
                valid_layer = 1;
                NEXT:
            }
            free(offset[i]);
        }
        free(offset);
        free(queue[cursor]);
        cursor++;
    }

    if (cursor != queue_size) {
        for (int i = cursor; cursor < queue_size-1; i++) {
            free(queue[i]);
        }
    }
    free(queue);
    fclose(fp);
    return 1;
}