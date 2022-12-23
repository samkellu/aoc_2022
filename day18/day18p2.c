#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[64];
    FILE* fp = fopen("day18.in", "r");

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

    int x_dim = 0;
    int y_dim = 0;
    int z_dim = 0;

    int num_values = 0;
    int** values = malloc(sizeof(int*) * 0);

    while (fgets(buf, 64, fp)) {
        
        values = realloc(values, sizeof(int*) * ++num_values);
        values[num_values-1] = malloc(sizeof(int)*3);

        values[num_values-1][0] = atoi(strtok(buf, ",")) + 1;
        values[num_values-1][1] = atoi(strtok(NULL, ",")) + 1;
        values[num_values-1][2] = atoi(strtok(NULL, ",")) + 1;

        x_dim = values[num_values-1][0] + 3 > x_dim ? values[num_values-1][0] + 3 : x_dim;
        y_dim = values[num_values-1][1] + 3 > y_dim ? values[num_values-1][1] + 3 : y_dim;
        z_dim = values[num_values-1][2] + 3 > z_dim ? values[num_values-1][2] + 3: z_dim;
    }
    fclose(fp);

    int*** coords = malloc(x_dim*sizeof(int**));
    for (int i = 0; i < x_dim; i++) {
        coords[i] = malloc(y_dim*sizeof(int*));
        for (int j = 0; j < y_dim; j++) {
            coords[i][j] = calloc(z_dim, sizeof(int));
        }
    }

    for (int i = 0; i < num_values; i++) {
        coords[values[i][0]][values[i][1]][values[i][2]] = 1;
        free(values[i]);
    }
    free(values);

    // BFS to find all cubes of air, run SA calculation during traverse

    int** visited = malloc(0);
    int num_visited = 0;
    int** queue = malloc(sizeof(int*));
    int queue_end = 1;
    int queue_start = 0;
    queue[0] = malloc(sizeof(int) * 3);
    queue[0][0] = 0;
    queue[0][1] = 0;
    queue[0][2] = 0;

    int total_area = 0;

    while (queue_start != queue_end) {
        
        visited = realloc(visited, sizeof(int*) * ++num_visited);
        visited[num_visited-1] = malloc(sizeof(int) * 3);
        visited[num_visited-1][0] = queue[queue_start][0];
        visited[num_visited-1][1] = queue[queue_start][1];
        visited[num_visited-1][2] = queue[queue_start][2];

        for (int i = 0; i < 6; i++) {
            int x_pos, y_pos, z_pos;

            x_pos = queue[queue_start][0]+positions[i][0];
            y_pos = queue[queue_start][1]+positions[i][1];
            z_pos = queue[queue_start][2]+positions[i][2];

            if (x_pos < 0 || x_pos >= x_dim || y_pos < 0 || y_pos >= y_dim || z_pos < 0 || z_pos >= z_dim) {
                continue;
            }

            if (coords[x_pos][y_pos][z_pos] == 1) {
                total_area++;
            } else {

                int valid = 1;
                for (int j = 0; j < num_visited; j++) {
                    if (visited[j][0] == x_pos && visited[j][1] == y_pos && visited[j][2] == z_pos) {
                        valid = 0;
                        break;
                    }
                }
                for (int j = queue_start; j < queue_end; j++) {
                    if (queue[j][0] == x_pos && queue[j][1] == y_pos && queue[j][2] == z_pos) {
                        valid = 0;
                        break;
                    }
                }

                if (valid) {
                    queue = realloc(queue, sizeof(int*) * ++queue_end);
                    queue[queue_end-1] = malloc(sizeof(int) * 3);
                    queue[queue_end-1][0] = x_pos;
                    queue[queue_end-1][1] = y_pos;
                    queue[queue_end-1][2] = z_pos;
                }
            }
        }
        free(queue[queue_start++]);
    }

    free(queue);

    for (int i = 0; i < num_visited; i++) {
        free(visited[i]);
    }
    free(visited);

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