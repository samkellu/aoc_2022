#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char buf[32];
    FILE* fp = fopen("day10.in", "r");

    int x_reg, cycle, total, skip_flag;
    cycle = x_reg = 1;

    char** screen = malloc(sizeof(char*) * 6);
    for (int i = 0; i < 6; i++) {
        char* line = malloc(sizeof(char) * 40);
        for (int j = 0; j < 40; j++) {
            line[j] = '.';
        }
        screen[i] = line;
    }

    int scan_x = 0; int scan_y = 0;

    while (fgets(buf, 32, fp)) {
        if (x_reg-1 == (cycle-1)%40 || x_reg == (cycle-1)%40 || x_reg+1 == (cycle-1)%40) {
            screen[(int)cycle/40][(cycle-1)%40] = '#';
        }
        cycle++;  

        if (strcmp(strtok(buf, " "), "addx") == 0) {
            if (x_reg-1 == (cycle-1)%40 || x_reg == (cycle-1)%40 || x_reg+1 == (cycle-1)%40) {
                screen[(int)cycle/40][(cycle-1)%40] = '#';
            }
            cycle++;
            x_reg += atoi(strtok(NULL, " "));
            continue;
        }        
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 6; i++) {
        free(screen[i]);
    }
    free(screen); 
    fclose(fp);
}