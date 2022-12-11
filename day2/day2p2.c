#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf[8];
    FILE* fp = fopen("day2.in", "r");

    int score = 0;

    while (fgets(buf, 8, fp)) {
        switch (buf[2]) {
            case 'X':
                score += (buf[0] == 'A' ? 3 : 0);
                score += (buf[0] == 'B' ? 1 : 0);
                score += (buf[0] == 'C' ? 2 : 0);
                break;

            case 'Y':
                score += 3;
                score += (buf[0] == 'A' ? 1 : 0);
                score += (buf[0] == 'B' ? 2 : 0);
                score += (buf[0] == 'C' ? 3 : 0);
                break;

            case 'Z':  
                score += 6;          
                score += (buf[0] == 'A' ? 2 : 0);
                score += (buf[0] == 'B' ? 3 : 0);
                score += (buf[0] == 'C' ? 1 : 0);
                break;
        };
    }
    printf("%d\n", score);

    fclose(fp);
}