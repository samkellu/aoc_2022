#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[128];
    FILE* fp = fopen("day15.in", "r");

    int maxx, maxy, minx, miny;
    maxx = maxy = 0;
    minx = miny = -1;
    char* tok;
    int** sensors = malloc(0);
    int num_sensors = 0;
    int** beacons = malloc(0);
    // int reading_level = 10;
    int reading_level = 2000000;

    while (fgets(buf, 128, fp)) {

        sensors = realloc(sensors, sizeof(int*)*++num_sensors);
        beacons = realloc(beacons, sizeof(int*)*num_sensors);
        tok = strtok(buf, " ");
        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");

        char* x = strsep(&tok, "=");
        x = strsep(&tok, "=");
        tok = strtok(NULL, " ");
        char* y = strsep(&tok, "=");
        y = strsep(&tok, "=");

        sensors[num_sensors-1] = malloc(sizeof(int)*2);
        sensors[num_sensors-1][0] = atoi(x);
        sensors[num_sensors-1][1] = atoi(y);

        minx = sensors[num_sensors-1][0] < minx || minx == -1 ? sensors[num_sensors-1][0] : minx;
        maxx = sensors[num_sensors-1][0] > maxx ? sensors[num_sensors-1][0] : maxx;

        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");
        tok = strtok(NULL, " ");

        char* bx = strsep(&tok, "=");
        bx = strsep(&tok, "=");
        tok = strtok(NULL, " ");
        char* by = strsep(&tok, "=");
        by = strsep(&tok, "=");    

        beacons[num_sensors-1] = malloc(sizeof(int)*2);
        beacons[num_sensors-1][0] = atoi(bx);
        beacons[num_sensors-1][1] = atoi(by);

        miny = sensors[num_sensors-1][1] < miny || miny == -1 ? sensors[num_sensors-1][1] : miny;
        maxy = sensors[num_sensors-1][1] > maxy ? sensors[num_sensors-1][1] : maxy;
    }

    int** values = malloc(0);
    int num_values = 0;

    for (int i = 0; i < num_sensors; i++) {
        int dist = abs(sensors[i][0]-beacons[i][0]) + abs(sensors[i][1] - beacons[i][1]);
        if (sensors[i][1] < reading_level && sensors[i][1] + dist > reading_level ||
            sensors[i][1] > reading_level && sensors[i][1] - dist < reading_level) {

            int lim = dist - (abs(reading_level-sensors[i][1]));
            values = realloc(values, sizeof(int*)*++num_values);
            values[num_values-1] = malloc(sizeof(int)*2);
            values[num_values-1][0] = sensors[i][0]-lim;
            values[num_values-1][1] = sensors[i][0]+lim;
        }
    }

    for (int i = 0; i < num_values; i++) {
        for (int j = 0; j < num_values; j++) {
            if (values[i][0] <= values[j][0] && values[i][1] >= values[j][1]) {

                values[j][0] = values[i][0];
                values[j][1] = values[i][1];

            } else if (values[i][0] <= values[j][0] && values[i][1] <= values[j][1] 
                && values[i][1] >= values[j][0]) {

                values[j][0] = values[i][0];
                values[i][1] = values[j][1];

            } else if (values[i][1] >= values[j][1] && values[i][0] <= values[j][1] 
                && values[i][0] >= values[j][0]) {

                values[j][1] = values[i][1];
                values[i][0] = values[j][0];

            } else if (values[i][1] == values[j][0]) {
                
                values[j][0] = values[i][0];
                values[i][1] = values[j][1];

            }  else if (values[i][0] == values[j][1]) {
                
                values[i][0] = values[j][0];
                values[j][1] = values[i][1];
            }
        }
    }

    int* at_read = malloc(sizeof(int)*num_sensors);
    int read_count = 0;

    for (int i = 0; i < num_sensors; i++) {
        if (beacons[i][1] == reading_level) {

            int valid = 1;
            for (int j = 0; j < read_count; j++) {
                if (at_read[j] == beacons[i][0]) {
                    valid = 0;
                }
            }

            if (valid) {
                at_read[read_count++] = beacons[i][0];
            }
        }
    }

    int to_subtract = 0;

    for (int i = 0; i < read_count; i++) {
        if (at_read[i] > values[0][0] && at_read[i] < values[0][1]) {
            to_subtract++;
        }
    }

    free(at_read);

    for (int i = 0; i < num_values; i++) {
        printf("%d\n", values[i][1]-values[i][0] - to_subtract+1);
    }

    for (int i = 0; i < num_values; i++) {
        free(values[i]);
    }
    free(values);
    for (int i = 0; i < num_sensors; i++) {
        free(sensors[i]);
        free(beacons[i]);
    }
    free(sensors);
    free(beacons);
    fclose(fp);
}