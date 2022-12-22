#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[64];
    FILE* fp = fopen("day18.in", "r");

    int x_dim = 50;
    int y_dim = 50;
    int z_dim = 50;
    int*** coords = malloc(x_dim*sizeof(int**));
    for (int i = 0; i < x_dim; i++) {
        coords[i] = malloc(y_dim*sizeof(int*));
        for (int j = 0; j < y_dim; j++) {
            coords[i][j] = calloc(z_dim, sizeof(int));
        }
    }

    int** positions = malloc(sizeof(int*) * 6);
    for (int i = 0; i < 6; i++) {
        positions[i] = malloc(sizeof(int)*3);
    }

    positions[0][0] = 0;
    positions[0][1] = 0;
    positions[0][2] = 1;

    positions[1][0] = 0;
    positions[1][1] = 0;
    positions[1][2] = -1;

    positions[2][0] = 1;
    positions[2][1] = 0;
    positions[2][2] = 0;

    positions[3][0] = -1;
    positions[3][1] = 0;
    positions[3][2] = 0;

    positions[4][0] = 0;
    positions[4][1] = 1;
    positions[4][2] = 0;

    positions[5][0] = 0;
    positions[5][1] = -1;
    positions[5][2] = 0;

    while (fgets(buf, 64, fp)) {
        coords[atoi(strtok(buf, ","))][atoi(strtok(NULL, ","))][atoi(strtok(NULL, ","))] = 1;
    }
    fclose(fp);

    for (int z = 0; z < 50; z++) {
        for (int u = 0; u < z_dim; u++) {
            for (int i = 0; i < x_dim; i++) {
                for (int j = 0; j < y_dim; j++) {
                    if (coords[i][j][u] == 0) {
                        int v1, v2, v3, v4, v5, v6;
                        v1 = v2 = v3 = v4 = v5 = v6 = 0;
                        for (int l = i; l < x_dim; l++) {
                            if (coords[l][j][u] == 1) {
                                v1 = 1;
                                break;
                            }
                        }
                        for (int l = i; l >= 0; l--) {
                            if (coords[l][j][u] == 1) {
                                v2 = 1;
                                break;
                            }
                        }
                        for (int l = j; l >= 0; l--) {
                            if (coords[i][l][u] == 1) {
                                v3 = 1;
                                break;
                            }
                        }
                        for (int l = j; l < y_dim; l++) {
                            if (coords[i][l][u] == 1) {
                                v4 = 1;
                                break;
                            }
                        }
                        for (int l = j; l >= 0; l--) {
                            if (coords[i][j][l] == 1) {
                                v5 = 1;
                                break;
                            }
                        }
                        for (int l = j; l < z_dim; l++) {
                            if (coords[i][j][l] == 1) {
                                v6 = 1;
                                break;
                            }
                        }
                        if (v1 && v2 && v3 && v4 && v5 && v6) {
                            printf("%d %d %d: %d %d %d %d %d %d\n", i, j, u, v1, v2, v3, v4, v5, v6);
                            coords[i][j][u] = 1;

                            // for (int l = i; l < x_dim; l++) {
                            //     if (coords[l][j][u] == 1) {
                            //         break;
                            //     }
                            //     coords[l][j][u] = 1;
                            // }
                                
                            // for (int l = i; l >= 0; l--) {
                            //     if (coords[l][j][u] == 1) {
                            //         break;
                            //     }
                            //     coords[l][j][u] = 1;
                            // }
                            // for (int l = j; l >= 0; l--) {
                            //     if (coords[i][l][u] == 1) {
                            //         break;
                            //     }
                            //     coords[i][l][u] = 1;
                            // }
                            // for (int l = j; l < y_dim; l++) {
                            //     if (coords[i][l][u] == 1) {
                            //         break;
                            //     }
                            //     coords[i][l][u] = 1;
                            // }
                            // for (int l = j; l >= 0; l--) {
                            //     if (coords[i][j][l] == 1) {
                            //         break;
                            //     }
                            //     coords[i][j][l] = 1;
                            // }
                            // for (int l = j; l < z_dim; l++) {
                            //     if (coords[i][j][l] == 1) {
                            //         break;
                            //     }
                            //     coords[i][j][l] = 1;
                            // }
                        }
                    }
                }
            }
        }
    }

    int total_area = 0;
    for (int i = 0; i < x_dim; i++) {
        for (int j = 0; j < y_dim; j++) {
            for (int u = 0; u < z_dim; u++) {
                if (coords[i][j][u] == 1) {
                    int count = 6;
                    for (int k = 0; k < 6; k++) {
                        if (i != 0 && i != x_dim-1 && j != 0 && j != y_dim-1 && u != 0 && u != z_dim-1) {
                            if (coords[i+positions[k][0]][j+positions[k][1]][u+positions[k][2]] == 1) {

                                count--;
                            }
                        }
                    }
                    total_area += count;
                }
            }
        }
    }

    for (int i = 0; i < x_dim; i++) {
        for (int j = 0; j < y_dim; j++) {
            free(coords[i][j]);
        }
        free(coords[i]);
    }
    free(coords);

    for (int i = 0; i < 6; i++) {
        free(positions[i]);
    }
    free(positions);

    printf("Total surface area: %d\n", total_area);
}