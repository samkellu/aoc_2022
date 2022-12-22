#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[64];
    FILE* fp = fopen("day18.in", "r");

    int** coords = malloc(0);
    int num_coords = 0;

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
        coords = realloc(coords, sizeof(int*) * ++num_coords);
        coords[num_coords-1] = malloc(sizeof(int) * 4);
        coords[num_coords-1][0] = atoi(strtok(buf, ","));
        coords[num_coords-1][1] = atoi(strtok(NULL, ","));
        coords[num_coords-1][2] = atoi(strtok(NULL, ","));
        coords[num_coords-1][3] = 6;
    }
    fclose(fp);

    for (int i = 0; i < num_coords; i++) {
        for (int j = 0; j < num_coords; j++) {
            for (int k = 0; k < 6; k++) {
                if (coords[j][0] == coords[i][0] + positions[k][0] && 
                    coords[j][1] == coords[i][1] + positions[k][1] &&
                    coords[j][2] == coords[i][2] + positions[k][2]) {

                    coords[i][3]--;
                }
            }
        }
    }

    int total_area = 0;
    for (int i = 0; i < num_coords; i++) {
        total_area += coords[i][3];
        free(coords[i]);
    }
    free(coords);

    for (int i = 0; i < 6; i++) {
        free(positions[i]);
    }
    free(positions);

    printf("Total surface area: %d\n", total_area);
}