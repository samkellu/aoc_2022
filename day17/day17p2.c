#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char buf[16384];
    FILE* fp = fopen("day17.in", "r");

    int num_shapes = 5;
    int shape_size[5] = { 4, 5, 5, 4, 4};
    int*** shapes = malloc(sizeof(int**) * 5);
    
    for (int i = 0; i < num_shapes; i++) {
        shapes[i] = malloc(sizeof(int**)*shape_size[i]);
        for (int j = 0; j < shape_size[i]; j++) {
            shapes[i][j] = malloc(sizeof(int)*2);
        }
    }

    // ####
    shapes[0][0][0] = 2;
    shapes[0][0][1] = 0;
    shapes[0][1][0] = 3;
    shapes[0][1][1] = 0;
    shapes[0][2][0] = 4;
    shapes[0][2][1] = 0;
    shapes[0][3][0] = 5;
    shapes[0][3][1] = 0;

    //  # 
    // ###
    //  # 
    shapes[1][0][0] = 3;
    shapes[1][0][1] = 0;
    shapes[1][1][0] = 2;
    shapes[1][1][1] = 1;
    shapes[1][2][0] = 3;
    shapes[1][2][1] = 1;
    shapes[1][3][0] = 4;
    shapes[1][3][1] = 1;
    shapes[1][4][0] = 3;
    shapes[1][4][1] = 2;

    //   #
    //   #
    // ###
    shapes[2][0][0] = 4;
    shapes[2][0][1] = 0;
    shapes[2][1][0] = 4;
    shapes[2][1][1] = 1;
    shapes[2][2][0] = 4;
    shapes[2][2][1] = 2;
    shapes[2][3][0] = 3;
    shapes[2][3][1] = 0;
    shapes[2][4][0] = 2;
    shapes[2][4][1] = 0;

    // #
    // #
    // #
    // #
    shapes[3][0][0] = 2;
    shapes[3][0][1] = 0;
    shapes[3][1][0] = 2;
    shapes[3][1][1] = 1;
    shapes[3][2][0] = 2;
    shapes[3][2][1] = 2;
    shapes[3][3][0] = 2;
    shapes[3][3][1] = 3;

    // ##
    // ##
    shapes[4][0][0] = 2;
    shapes[4][0][1] = 0;
    shapes[4][1][0] = 3;
    shapes[4][1][1] = 0;
    shapes[4][2][0] = 2;
    shapes[4][2][1] = 1;
    shapes[4][3][0] = 3;
    shapes[4][3][1] = 1;

    int shape_num = -1;

    long long int num_levels = 7;
    int** map = malloc(num_levels*sizeof(int*));
    for (int i = 0; i < num_levels; i++) {
        map[i] = calloc(7, sizeof(int));
    }

    fgets(buf, 16384, fp);
    fclose(fp);

    int at_rest = 1;
    int** cur_shape;
    long long int y_offset = 0;
    int cursor = 0;
    long long int num_rocks = 0;
    int direction = 0;

    while (1) {        

        if (cursor >= strlen(buf)) {
            cursor = 0;
        }
        direction = buf[cursor++] == '>' ? 1 : -1;
        
        if (at_rest) {
            if (num_rocks % 1000000 == 0) {
                printf("%d\n", num_rocks);
            }
            if (num_rocks++ == 1000000000000) {
                for (int i = num_levels-1; i >= 0; i--) {
                    for (int j = 0; j < 7; j++) {
                        if (map[i][j] == 1 || i == 0) {
                            printf("%d\n", i+1);
                            goto EXIT;
                        }
                    }
                }
                EXIT:
                break;
            }

            for (int i = num_levels-1; i >= 0; i--) {
                for (int j = 0; j < 7; j++) {
                    if (map[i][j] == 1) {
                        y_offset = i+4;
                        goto BREAK;
                    }

                    if (i == 0 && j == 6) {
                        y_offset = i+3;
                        goto BREAK;
                    }
                }
            }
            BREAK:
            map = realloc(map, (y_offset + 8)*sizeof(int*));

            for (int i = num_levels; i < y_offset + 8; i++) {
                map[i] = calloc(7, sizeof(int));
            }
            num_levels = y_offset + 8;

            at_rest = 0;
            shape_num = (shape_num+1) % num_shapes;
            cur_shape = malloc(sizeof(int*) * shape_size[shape_num]);
            
            for (int i = 0; i < shape_size[shape_num]; i++) {
                cur_shape[i] = malloc(sizeof(int) * 2);
                cur_shape[i][0] = shapes[shape_num][i][0];
                cur_shape[i][1] = shapes[shape_num][i][1] + y_offset;
            }
        }

        int valid = 1;
        for (int i = 0; i < shape_size[shape_num]; i++) {
            if (cur_shape[i][0] + direction >= 7 || cur_shape[i][0] + direction < 0 || 
                map[cur_shape[i][1]][cur_shape[i][0] + direction] == 1) {
                valid = 0;
                break;
            }
        }

        if (valid) {
            for (int i = 0; i < shape_size[shape_num]; i++) {
                cur_shape[i][0] += direction;
            }
        }
        // printf("%d\n", direction);
        // for (int y = num_levels-1; y >= 0; y--) {
        //     printf("|");
        //     for (int x = 0; x < 7; x++) {
        //         for (int l = 0; l < shape_size[shape_num]; l++) {
        //             if (cur_shape[l][0] == x && cur_shape[l][1] == y) {
        //                 printf("@");
        //                 goto NEXT1;
        //             }
        //         }
        //         if (map[y][x] == 1) {
        //             printf("#");
        //         } else {
        //             printf(" ");
        //         }
        //         NEXT1:
        //     }
        //     printf("| %d\n", y);
        // }
        // printf("+-------+\n\n");
        // usleep(400000);

        for (int i = 0; i < shape_size[shape_num]; i++) {
            if (cur_shape[i][1] == 0 || map[cur_shape[i][1] - 1][cur_shape[i][0]] == 1) {
                at_rest = 1;
                break;
            }
        }
        if (!at_rest) {
            for (int i = 0; i < shape_size[shape_num]; i++) {
                cur_shape[i][1]--;
            }
            // for (int y = num_levels-1; y >= 0; y--) {
            //     printf("|");
            //     for (int x = 0; x < 7; x++) {
            //         for (int l = 0; l < shape_size[shape_num]; l++) {
            //             if (cur_shape[l][0] == x && cur_shape[l][1] == y) {
            //                 printf("@");
            //                 goto NEXT2;
            //             }
            //         }
            //         if (map[y][x] == 1) {
            //             printf("#");
            //         } else {
            //             printf(" ");
            //         }
            //         NEXT2:
            //     }
            //     printf("| %d\n", y);
            // }
            // printf("+-------+\n\n");
            // usleep(400000);
        } else {
            for (int i = 0; i < shape_size[shape_num]; i++) {
                map[cur_shape[i][1]][cur_shape[i][0]] = 1;
                free(cur_shape[i]);
            }
            free(cur_shape);
        }
    }
    for (int i = 0; i < num_levels; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < num_shapes; i++) {
        for (int j = 0; j < shape_size[i]; j++) {
            free(shapes[i][j]);
        }
        free(shapes[i]);
    }
    free(shapes);
}