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

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_columns; col++) {

            for (int left = 0; left < col; left++) {
                if (values[row][left] >= values[row][col]) {
                    goto NEXT0;
                } 
            }
            count++;
            continue;

            NEXT0:
            for (int right = num_columns-1; right > col; right--) {
                if (values[row][right] >= values[row][col]) {
                    goto NEXT1;
                } 
            }
            count++;
            continue;

            NEXT1:
            for (int up = 0; up < row; up++) {
                if (values[up][col] >= values[row][col]) {
                    goto NEXT2;
                } 
            }
            count++;
            continue;

            NEXT2:
            for (int down = num_rows-1; down > row; down--) {
                if (values[down][col] >= values[row][col]) {
                    goto NEXT3;
                } 
            }
            count++;
            continue;

            NEXT3:
        }
    }
    printf("%d\n", count);

    free(values);
    fclose(fp);
}