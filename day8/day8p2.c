#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[128];
    int** values = malloc(sizeof(int*));
    FILE* fp = fopen("day8.in", "r");

    int count = 0;
    int num_columns = 99;
    int num_rows = 0;

    while (fgets(buf, 128, fp)) {

        values = realloc(values, sizeof(int*)*(num_rows+1));
        values[num_rows] = malloc(sizeof(int)*(num_columns));

        for (int i = 0; i < 99; i++) {
            values[num_rows][i] = (int) buf[i];
        }
        num_rows++;
    }

    int l_dist, r_dist, u_dist, d_dist, max;
    max = 0;

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_columns; col++) {
            l_dist = r_dist = u_dist = d_dist = 0;

            for (int left = col; left >= 0; left--) {
                l_dist = col-left;
                if (left != col && values[row][left] >= values[row][col]) {
                    break;
                } 
            }

            for (int right = col; right < num_columns; right++) {
                r_dist = right-col;
                if (right != col && values[row][right] >= values[row][col]) {
                    break;
                } 
            }

            for (int up = row; up >= 0; up--) {
                u_dist = row-up;
                if (up != row && values[up][col] >= values[row][col]) {
                    break;
                } 
            }

            for (int down = row; down < num_rows; down++) {
                d_dist = down-row;
                if (down != row && values[down][col] >= values[row][col]) {
                    break;
                } 
            }

            max = l_dist * r_dist * u_dist * d_dist > max ? l_dist * r_dist * u_dist * d_dist : max;
        }
    }
    printf("%d\n", max);

    free(values);
    fclose(fp);
}