#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char buf[32];
    FILE* fp = fopen("day10.in", "r");

    int x_reg, cycle, total, skip_flag;
    cycle = x_reg = 1;
    total = 0;

    while (fgets(buf, 32, fp)) {
        if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
            total += x_reg * cycle;
        }       
        cycle++;  

        if (strcmp(strtok(buf, " "), "addx") == 0) {
            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
                total += x_reg * cycle;
            }            
            cycle++;
            x_reg += atoi(strtok(NULL, " "));
            continue;
        }        
    }
    printf("%d\n", total);
    fclose(fp);
}